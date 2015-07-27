#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>

#include <ilcplex/ilocplex.h>

#define T_MAX 33
#define n 11         //Number of Mixing Operations
#define n_m 2        //Numer of Mixers
#define T 3          //Operation Time
#define E 14         //Edges between mix nodes

using namespace std;

IloEnv env;
IloModel model(env);
IloNumVarArray s(env);  
IloRangeArray c(env);
IloCplex cplex(model);

typedef IloArray<IloBoolVarArray> BoolVarMatrix;
void  Create2DArray(IloModel model, BoolVarMatrix m);

typedef IloArray<BoolVarMatrix> BoolVar3DMatrix;
void Create3DArray(IloModel model, BoolVar3DMatrix m, int size);

void PopulateFromGraph(IloModel model, IloNumVarArray s, IloRangeArray c); 
void CreateSchedulingConstraint(IloModel model, BoolVarMatrix X, BoolVarMatrix Y,
				IloNumVarArray s, IloRangeArray c);
void CreateBindingConstraint(IloModel model, BoolVarMatrix M,  BoolVarMatrix R,
			     BoolVarMatrix Y, BoolVarMatrix X, IloRangeArray c);
void AddtionalConstraint(IloModel model, BoolVar3DMatrix L, BoolVarMatrix M, 
			 BoolVarMatrix X, BoolVar3DMatrix G, BoolVarMatrix R,
			 BoolVarMatrix Y, IloRangeArray c);

int main(){
  try{
    PopulateFromGraph(model, s, c);

    BoolVarMatrix X(env, n);
    Create2DArray(model, X);
    BoolVarMatrix Y(env, E);
    Create2DArray(model, X);
    CreateSchedulingConstraint(model, X, Y, s, c);
    
    BoolVarMatrix M(env, n_m);
    Create2DArray(model, M);
    BoolVarMatrix R(env, n_m);
    Create2DArray(model, R);
    CreateBindingConstraint(model, M, R, Y, X, c);
    
    BoolVar3DMatrix L(env, n_m);
    Create3DArray(model, L, n);
    BoolVar3DMatrix G(env, n_m);
    Create3DArray(model, G, E);
    AddtionalConstraint(model, L,  M, X, G, R, Y, c); 

    model.add(c);
    
    cplex.exportModel("ilp1.lp");
    cplex.solve();

    env.out() << "Status: " << cplex.getStatus() << endl;
  
    IloNumArray vals(env);
    cplex.getValues(vals, s);
    env.out() << "Schedule    " << vals << endl;
    cplex.getValues(vals, M[0]);
    env.out() << "Module 1    " << vals << endl;
    cplex.getValues(vals, M[1]);
    env.out() << "Module 2    " << vals << endl;
    cplex.getValues(vals, M[2]);
    env.out() << "Module 3    " << vals << endl;
    
  }
  catch(IloException& e){
    cerr << "Error: " << e << endl;
  }
  catch(...){
    cerr << "Unknown" << endl;
  }
  env.end();
  return 0;
}


void Create2DArray(IloModel model, BoolVarMatrix m){
  IloEnv env = model.getEnv();
  for(int i = 0; i < m.getSize(); i++){
    m[i]=IloBoolVarArray(env);
  }
  return;
}

void Create3DArray(IloModel model, BoolVar3DMatrix R, int size){
  IloEnv env = model.getEnv();
  for(int p = 0; p < R.getSize(); p++)
    R[p] = BoolVarMatrix(env, E);
  for(int p = 0; p < R.getSize(); p++){
    for(int e = 0; e < size; e++)
      R[p][e]=IloBoolVarArray(env);
  }
  return;
}

void PopulateFromGraph(IloModel model, IloNumVarArray s, IloRangeArray c){
  IloEnv env = model.getEnv();
  for(int i = 0; i < n; i++)
    s.add(IloNumVar(env));
  model.add(IloMinimize(env, s[7]));
  
  //To Start Enumeration from 1
  c.add(s[0] == 100);
  
  //Every edge bears a constraint    |Edge No.
  c.add(s[2] - s[1] >= T);//         |1
  c.add(s[3] - s[2] >= T);//         |2
  c.add(s[4] - s[3] >= T);//         |3
  c.add(s[4] - s[2] >= T);//         |4
  c.add(s[5] - s[4] >= T);//         |5
  c.add(s[6] - s[4] >= T);//         |6
  c.add(s[6] - s[2] >= T);//         |7
  c.add(s[7] - s[6] >= T);//         |8
  c.add(s[8] - s[5] >= T);//         |9
  c.add(s[9] - s[8] >= T);//         |10
  c.add(s[10]- s[8] >= T);//         |11
  c.add(s[10]- s[7] >= T);//         |12
  c.add(s[11]- s[6] >= T);//         |13
  c.add(s[11]- s[9] >= T);//         |14
  
  //Dummy Variable s[12]
  c.add(s[12]- s[11]>= 0);
  c.add(s[12]- s[10] >= 0);
}

void CreateSchedulingConstraint(IloModel model, BoolVarMatrix Y, BoolVarMatrix X, 
				IloNumVarArray s, IloRangeArray c){
  IloEnv env = model.getEnv();
  IloExprArray sum(env);
  IloExprArray sum2(env);
  IloExprArray summation1(env);
  IloExprArray summation2(env);
  for(int i = 0; i < X.getSize(); i++){
    sum.add(IloExpr(env));
    for(int t = 0; t < T_MAX; t++){
      X[i].add(IloBoolVar(env)); 
      sum[i] +=  X[i][t];
      c.add( t - s[i] - T_MAX*(X[i][t]-1)     >= 0);
      c.add(-t + s[i] - T_MAX*(X[i][t]-1) + T >= 1);
    }
    c.add(sum[i] == T);
  }

  //Manual Formulation

  //Edge-1
  sum2.add(IloExpr(env));
  for(int t = 0; t < T_MAX; t++){
    Y[0].add(IloBoolVar(env)); 
    sum2[0] +=  Y[0][t];
    c.add( t - (s[1] + T) - T_MAX*(Y[0][t]-1)     >= 0);
    c.add(-t +  s[2]      - T_MAX*(Y[0][t]-1) + T >= 1);
  }
  c.add(sum2[0] - (s[2]-(s[1]+T)) == 0);

  //Edge-2
  sum2.add(IloExpr(env));
  for(int t = 0; t < T_MAX; t++){
    Y[1].add(IloBoolVar(env)); 
    sum2[1] +=  Y[1][t];
    c.add( t - (s[2] + T) - T_MAX*(Y[0][t]-1)     >= 0);
    c.add(-t +  s[3]      - T_MAX*(Y[0][t]-1) + T >= 1);
  }
  c.add(sum2[1] - (s[3]-(s[2]+T)) == 0);
	
  //Edge-3
  sum2.add(IloExpr(env));
  for(int t = 0; t < T_MAX; t++){
    Y[2].add(IloBoolVar(env)); 
    sum2[2] +=  Y[2][t];
    c.add( t - (s[3] + T) - T_MAX*(Y[2][t]-1)     >= 0);
    c.add(-t +  s[4]      - T_MAX*(Y[2][t]-1) + T >= 1);
  }
  c.add(sum2[2] - (s[4]-(s[3]+T)) == 0);

  //Edge-4
  sum2.add(IloExpr(env));
  for(int t = 0; t < T_MAX; t++){
    Y[3].add(IloBoolVar(env)); 
    sum2[3] +=  Y[3][t];
    c.add( t - (s[2] + T) - T_MAX*(Y[3][t]-1)     >= 0);
    c.add(-t +  s[4]      - T_MAX*(Y[3][t]-1) + T >= 1);
  }
  c.add(sum2[3] - (s[4]-(s[2]+T)) == 0);

  //Edge-5
  sum2.add(IloExpr(env));
  for(int t = 0; t < T_MAX; t++){
    Y[4].add(IloBoolVar(env)); 
    sum2[4] +=  Y[4][t];
    c.add( t - (s[4] + T) - T_MAX*(Y[4][t]-1)     >= 0);
    c.add(-t +  s[5]      - T_MAX*(Y[4][t]-1) + T >= 1);
  }
  c.add(sum2[4] - (s[5]-(s[4]+T)) == 0);


  //Edge-6
  sum2.add(IloExpr(env));
  for(int t = 0; t < T_MAX; t++){
    Y[5].add(IloBoolVar(env)); 
    sum2[5] +=  Y[5][t];
    c.add( t - (s[4] + T) - T_MAX*(Y[5][t]-1)     >= 0);
    c.add(-t +  s[6]      - T_MAX*(Y[5][t]-1) + T >= 1);
  }
  c.add(sum2[5] - (s[6]-(s[4]+T)) == 0); 


  //Edge-7
  sum2.add(IloExpr(env));
  for(int t = 0; t < T_MAX; t++){
    Y[6].add(IloBoolVar(env)); 
    sum2[6] +=  Y[6][t];
    c.add( t - (s[2] + T) - T_MAX*(Y[6][t]-1)     >= 0);
    c.add(-t +  s[6]      - T_MAX*(Y[6][t]-1) + T >= 1);
  }
  c.add(sum2[1] - (s[6]-(s[2]+T)) == 0);

  //Edge-8
  sum2.add(IloExpr(env));
  for(int t = 0; t < T_MAX; t++){
    Y[7].add(IloBoolVar(env)); 
    sum2[7] +=  Y[7][t];
    c.add( t - (s[6] + T) - T_MAX*(Y[7][t]-1)     >= 0);
    c.add(-t +  s[7]      - T_MAX*(Y[7][t]-1) + T >= 1);
  }
  c.add(sum2[7] - (s[7]-(s[6]+T)) == 0);
  
  //Edge-9
  sum2.add(IloExpr(env));
  for(int t = 0; t < T_MAX; t++){
    Y[8].add(IloBoolVar(env)); 
    sum2[8] +=  Y[8][t];
    c.add( t - (s[5] + T) - T_MAX*(Y[8][t]-1)     >= 0);
    c.add(-t +  s[8]      - T_MAX*(Y[8][t]-1) + T >= 1);
  }
  c.add(sum2[8] - (s[8]-(s[5]+T)) == 0);

  //Edge-10
  sum2.add(IloExpr(env));
  for(int t = 0; t < T_MAX; t++){
    Y[9].add(IloBoolVar(env)); 
    sum2[9] +=  Y[9][t];
    c.add( t - (s[8] + T) - T_MAX*(Y[9][t]-1)     >= 0);
    c.add(-t +  s[9]      - T_MAX*(Y[9][t]-1) + T >= 1);
  }
  c.add(sum2[9] - (s[9]-(s[8]+T)) == 0);

  //Edge-11
  sum2.add(IloExpr(env));
  for(int t = 0; t < T_MAX; t++){
    Y[10].add(IloBoolVar(env)); 
    sum2[10] +=  Y[10][t];
    c.add( t - (s[8] + T) - T_MAX*(Y[10][t]-1)     >= 0);
    c.add(-t +  s[10]     - T_MAX*(Y[10][t]-1) + T >= 1);
  }
  c.add(sum2[10] - (s[10]-(s[8]+T)) == 0);

  //Edge-12
  sum2.add(IloExpr(env));
  for(int t = 0; t < T_MAX; t++){
    Y[11].add(IloBoolVar(env)); 
    sum2[11] +=  Y[11][t];
    c.add( t - (s[7] + T) - T_MAX*(Y[11][t]-1)     >= 0);
    c.add(-t +  s[10]     - T_MAX*(Y[11][t]-1) + T >= 1);
  }
  c.add(sum2[11] - (s[10]-(s[7]+T)) == 0);

  //Edge-13
  sum2.add(IloExpr(env));
  for(int t = 0; t < T_MAX; t++){
    Y[12].add(IloBoolVar(env)); 
    sum2[12] +=  Y[12][t];
    c.add( t - (s[6] + T) - T_MAX*(Y[12][t]-1)     >= 0);
    c.add(-t +  s[11]     - T_MAX*(Y[12][t]-1) + T >= 1);
  }
  c.add(sum2[12] - (s[11]-(s[6]+T)) == 0);

  //Edge-14
  sum2.add(IloExpr(env));
  for(int t = 0; t < T_MAX; t++){
    Y[13].add(IloBoolVar(env)); 
    sum2[13] +=  Y[13][t];
    c.add( t - (s[9] + T) - T_MAX*(Y[13][t]-1)     >= 0);
    c.add(-t +  s[11]     - T_MAX*(Y[13][t]-1) + T >= 1);
  }
  c.add(sum2[13] - (s[11]-(s[9]+T)) == 0);
  
  //Chip Architecture Constraint
  for(int t = 0; t < T_MAX; t++){
    summation1.add(IloExpr(env));
    for(int i = 0; i < X.getSize(); i++){
      summation1[t] += X[i][t];
    }
    for(int e = 0; e < Y.getSize(); e++){
      summation2[t] += Y[e][t];
    }
    c.add(summation1[t] + summation2[t] <= n_m);
  }
  
  return;
}

void CreateBindingConstraint(IloModel model, BoolVarMatrix M, BoolVarMatrix R,
			     BoolVarMatrix Y, BoolVarMatrix X, IloNumVarArray s,
			     IloRangeArray c){
  IloEnv env = model.getEnv();
  IloExprArray sum(env);
  for(int p = 0; p < M.getSize(); p++){
    for(int i = 0; i < n; i++)
      M[p].add(IloBoolVar(env));
  }
  
  //Ensuring operation remains bound to the same module
  for(int i = 0; i < n; i++){
    sum.add(IloExpr(env));
    for(int p = 0; p < n_m; p++){
      sum[i] += M[p][i];
    }
    c.add(sum[i] == 1);
  }

  //Ensuring droplet remains bound to the same module
  for(int i = 0; i < E; i++){
    sum.add(IloExpr(env));
    for(int p = 0; p < n_m; p++){
      sum[i] += M[p][i];
    }
    c.add(sum[i] <= 1);
  }

  //Two operations running simulateneously can not be bound
  //to the same module
  for(int p = 0; p < n_m; p++){
    for(int t = 0; t < T_MAX; t++){
      for(int i = 0; i < n; i++){
	for(int j = i+1; j < n; j++){
	  c.add(X[i][t] + X[j][t] - M[p][i] - M[p][j] >= -2);
	  c.add(X[i][t] + X[j][t] + M[p][i] + M[p][j] <=  3);
	}
      }
    }
  }

  //Two droplets being stored simulateneously can not be bound
  //to the same module
  for(int p = 0; p < n_m; p++){
    for(int t = 0; t < T_MAX; t++){
      for(int i = 0; i < E; i++){
	for(int j = i+1; j < n; j++){
	  c.add(Y[i][t] + Y[j][t] - R[p][i] - R[p][j] >= -2);
	  c.add(Y[i][t] + Y[j][t] + R[p][i] + R[p][j] <=  3);
	}
      }
    }
  }
  return;
}

void AddtionalConstraint(IloModel model, BoolVar3DMatrix L, BoolVarMatrix M, 
			 BoolVarMatrix X, BoolVar3DMatrix G, BoolVarMatrix R,
			 BoolVarMatrix Y, IloRangeArray c){

  IloEnv env = model.getEnv();
  for(int p = 0; p < L.getSize(); p++){
    for(int i = 0; i < n; i++){
      for(int t = 0; t < T_MAX; t++){
	L[p][i].add(IloBoolVar(env));
	c.add(L[p][i][t] - M[p][i] - X[i][t] >= -1);
	c.add(L[p][i][t] - M[p][i] - X[i][t] <=  0);
	c.add(L[p][i][t] + M[p][i] - X[i][t] <=  1);
	c.add(L[p][i][t] - M[p][i] + X[i][t] <=  1);
      }
    }
  }

  for(int p = 0; p < G.getSize(); p++){
    for(int e = 0; e < E; e++){
      for(int t = 0; t < T_MAX; t++){
	G[p][i].add(IloBoolVar(env));
	c.add(G[p][e][t] - R[p][e] - Y[e][t] >= -1);
	c.add(G[p][e][t] - R[p][e] - X[e][t] <=  0);
	c.add(G[p][e][t] + R[p][e] - X[e][t] <=  1);
	c.add(G[p][e][t] - R[p][e] + X[e][t] <=  1);
      }
    }
  }

  for(int t = 0; t < T_MAX; t++){
    IloExprArray sum1(env);
    IloExprArray sum2(env);
    for(int p = 0; p < n_m; p++){
      sum1.add(IloExpr(env));
      sum2.add(IloExpr(env));
      
      for(int i = 0; i < n; i++){
	sum2[p] += L[p][i][t];
      }
      for(int e = 0; e < E; e++){
	sum2[p] += G[p][e][t];
      }
      c.add(sum1[p] + sum2[p] - 2 <=  -1);
    }
  }
  return;
}


