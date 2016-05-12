#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>

#include <ilcplex/ilocplex.h>

#define T_MAX 10
#define n 7         //Number of Mixing Operations
#define n_m 1       //Numer of Mixers
#define T 1         //Operation Time
#define E 6         //Edges between mix nodes

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
			     BoolVarMatrix Y, BoolVarMatrix X, IloNumVarArray s,
 			     IloRangeArray c);
void AddtionalConstraint(IloModel model, BoolVar3DMatrix L, BoolVarMatrix M, 
			 BoolVarMatrix X, BoolVar3DMatrix G, BoolVarMatrix R,
			 BoolVarMatrix Y, IloRangeArray c);

int main(){
  try{
    PopulateFromGraph(model, s, c);

    BoolVarMatrix X(env, n);
    Create2DArray(model, X);
    BoolVarMatrix Y(env, E);
    Create2DArray(model, Y);
    CreateSchedulingConstraint(model, X, Y, s, c);
  
    BoolVarMatrix M(env, n_m);
    Create2DArray(model, M);
    BoolVarMatrix R(env, n_m);
    Create2DArray(model, R);
    CreateBindingConstraint(model, M, R, Y, X, s, c);

    BoolVar3DMatrix L(env, n_m);
    Create3DArray(model, L, n);
    BoolVar3DMatrix G(env, n_m);
    Create3DArray(model, G, E);
    AddtionalConstraint(model, L,  M, X, G, R, Y, c); 

    model.add(c);
    
    cplex.exportModel("pcr.lp");
    cplex.solve();

    env.out() << "Status: " << cplex.getStatus() << endl;
  
    IloNumArray vals(env);
    cplex.getValues(vals, s);
    env.out() << "Schedule    " << vals << endl;
    cplex.getValues(vals, M[0]);
    env.out() << "Mix-Module 1    " << vals << endl;
    /*cplex.getValues(vals, M[1]);
    env.out() << "Mix-Module 2    " << vals << endl;
    cplex.getValues(vals, M[2]);
    env.out() << "Mix-Module 3    " << vals << endl;
    cplex.getValues(vals, R[0]);
    env.out() << "Storage-Module 1    " << vals << endl;
    cplex.getValues(vals, R[1]);
    env.out() << "Storage-Module 2    " << vals << endl;
    cplex.getValues(vals, R[2]);
    env.out() << "Storage-Module 3    " << vals << endl;*/
    
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

  // Used n+2 for accomodating two extra variables
  for(int i = 0; i < n+1; i++)
    s.add(IloNumVar(env));
  model.add(IloMinimize(env, s[7]));
  
  //To Start Enumeration from 1
  c.add(s[0] == 100);
  
  //Every edge bears a constraint    
  c.add(s[2] - s[1] >= T);         
  c.add(s[3] - s[2] >= T);
  c.add(s[4] - s[3] >= T);
  c.add(s[5] - s[4] >= T);
  c.add(s[6] - s[5] >= T);
  c.add(s[7] - s[6] >= T);
}

void CreateSchedulingConstraint(IloModel model, BoolVarMatrix X, BoolVarMatrix Y, 
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
      c.add( t - s[i+1] - T_MAX*(X[i][t]-1)     >= 0);
      c.add(-t + s[i+1] - T_MAX*(X[i][t]-1) + T >= 1);
    }
    c.add(sum[i] == T);
  }
  for(int e = 0; e < E; e++){
    sum2.add(IloExpr(env));
    for(int t = 0; t < T_MAX; t++){
      Y[e].add(IloBoolVar(env)); 
      sum2[e] +=  Y[e][t];
      c.add( t - (s[e+1] + T) - T_MAX*(Y[e][t]-1)     >= 0);
      c.add(-t +  s[e+2]      - T_MAX*(Y[e][t]-1)  >= 1);
    }
    c.add(sum2[e] - (s[e+2]-(s[e+1]+T)) == 0);
  }


  
  //Chip Architecture Constraint
  for(int t = 0; t < T_MAX; t++){
    summation1.add(IloExpr(env));
    summation2.add(IloExpr(env));
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
  IloExprArray sum1(env);
  IloExprArray sum2(env);
  for(int p = 0; p < M.getSize(); p++){
    for(int i = 0; i < n; i++)
      M[p].add(IloBoolVar(env));
  }
  for(int p = 0; p < R.getSize(); p++){
    for(int e = 0; e < E; e++)
      R[p].add(IloBoolVar(env));
  }

  //Ensuring operation remains bound to the same module
  for(int i = 0; i < n; i++){
    sum1.add(IloExpr(env));
    for(int p = 0; p < n_m; p++){
      sum1[i] += M[p][i];
    }
    c.add(sum1[i] == 1);
  }
 
  //Ensuring droplet remains bound to the same module
  for(int e = 0; e < E; e++){
    sum2.add(IloExpr(env));
    for(int p = 0; p < n_m; p++){
      sum2[e] += R[p][e];
    }
    c.add(sum2[e] <= 1);
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
	for(int j = i+1; j < E; j++){
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
	G[p][e].add(IloBoolVar(env));
	c.add(G[p][e][t] - R[p][e] - Y[e][t] >= -1);
	c.add(G[p][e][t] - R[p][e] - Y[e][t] <=  0);
	c.add(G[p][e][t] + R[p][e] - Y[e][t] <=  1);
	c.add(G[p][e][t] - R[p][e] + Y[e][t] <=  1);
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


