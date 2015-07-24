#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>

#include <ilcplex/ilocplex.h>

#define T_MAX 21
#define n 7          //Number of Mixing Operations
#define n_m 3        //Numer of Mixers
#define n_r 1        //Number of Reservoirs
#define T 3          //Operation Time
#define E 6          //Edges between mix nodes
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
void CreateSchedulingConstraint(IloModel model, BoolVarMatrix X, IloNumVarArray s,
				IloRangeArray c);
void CreateBindingConstraint(IloModel model, BoolVarMatrix M,  BoolVarMatrix X, 
			     IloRangeArray c);
void ReservoirConstraint(IloModel model, BoolVar3DMatrix R, BoolVarMatrix M,
			BoolVarMatrix X, IloRangeArray c);
void OutputDroplet(IloModel model, BoolVar3DMatrix Y, BoolVarMatrix M, 
		   BoolVarMatrix X, IloRangeArray c, BoolVar3DMatrix R);

int main(){
  try{
    PopulateFromGraph(model, s, c);

    BoolVarMatrix X(env, n);
    Create2DArray(model, X);
    CreateSchedulingConstraint(model, X, s, c);
    
    BoolVarMatrix M(env, n_m);
    Create2DArray(model, M);
    CreateBindingConstraint(model, M, X, c);
    
    BoolVar3DMatrix R(env, n_r);
    Create3DArray(model, R, E);
    ReservoirConstraint(model, R, M, X, c);
    
    BoolVar3DMatrix Y(env, n_m);
    Create3DArray(model, Y, n);
    OutputDroplet(model, Y, M, X, c, R);

    model.add(c);
    
    cplex.exportModel("ilp1.lp");
    cplex.solve();

    env.out() << "Status: " << cplex.getStatus() << endl;
  
    IloNumArray vals(env);
    cplex.getValues(vals, s);
    env.out() << "Schedule    " << vals << endl;
    cplex.getValues(vals, M[0]);
    env.out() << "Mixer 1    " << vals << endl;
    cplex.getValues(vals, M[1]);
    env.out() << "Mixer 2    " << vals << endl;
    cplex.getValues(vals, M[2]);
    env.out() << "Mixer 3    " << vals << endl;
    
    //Output Droplet() needs debugging
    /*for(int p = 0; p < n_r; p++){
      for(int e = 0; e < E; e++){
	cplex.getValues(vals, R[p][e]);
	env.out() << "Edge " << e <<" " << vals << endl;
      }
      }*/
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
  model.add(IloMinimize(env, s[6]));
     
  c.add(s[4] - s[1] >= T);
  c.add(s[4] - s[0] >= T);
  c.add(s[5] - s[2] >= T);
  c.add(s[5] - s[3] >= T);
  c.add(s[6] - s[4] >= T);
  c.add(s[6] - s[5] >= T);
}

void CreateSchedulingConstraint(IloModel model, BoolVarMatrix X, IloNumVarArray s,
				IloRangeArray c){
  IloEnv env = model.getEnv();
  IloExprArray sum(env);
  IloExprArray summation(env);
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
  //Mixer constraint
  for(int t = 0; t < T_MAX; t++){
    summation.add(IloExpr(env));
    for(int i = 0; i < X.getSize(); i++){
      summation[t] += X[i][t];
    }
    c.add(summation[t] <= n_m);
  }
  return;
}

void CreateBindingConstraint(IloModel model, BoolVarMatrix M, BoolVarMatrix X, 
			     IloRangeArray c){
  IloEnv env = model.getEnv();
  IloExprArray sum(env);
  for(int p = 0; p < M.getSize(); p++){
    for(int i = 0; i < n; i++)
      M[p].add(IloBoolVar(env));
  }
  
  //Ensuring operation remains bound to the same mixer
  for(int i = 0; i < n; i++){
    sum.add(IloExpr(env));
    for(int p = 0; p < n_m; p++){
      sum[i] += M[p][i];
    }
    c.add(sum[i] == 1);
  }
  //Two operations running simulateneously can not be bound
  //to the same mixer
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
  return;
}

void ReservoirConstraint(IloModel model, BoolVar3DMatrix R, BoolVarMatrix M,
			BoolVarMatrix X, IloRangeArray c){
  IloEnv env = model.getEnv();
  for(int p = 0; p < n_r; p++){
    for(int e = 0; e < E; e++){
      for(int t = 0; t < T_MAX; t++){
	R[p][e].add(IloBoolVar(env));
      }
    }
  }

  //A reservoir at a given time step holds at most one drop
  for(int p = 0; p < n_r; p++){
    IloExprArray sum(env);
    for(int t = 0; t < T_MAX; t++){
      sum.add(IloExpr(env));
      for(int e = 0; e < E; e++){
	sum[t] += R[p][e][t];
      }
      c.add(sum[t] <= 1);
    }
  }

  //A droplet at a given time step can be only in one reservoir
  IloExprArray sum1(env);
  for(int e = 0; e < E; e++){
    for(int t = 0; t < T_MAX; t++){
      sum1.add(IloExpr(env));
      for(int p = 0; p < n_r; p++){
	sum1[t + e*T_MAX] += R[p][e][t];
      }
      c.add(sum1[t] <= 1);
    }
  }

  //At any given time step, the max number of reservoirs being used
  //can be atmost n_r
  IloExprArray sum(env);
  IloExprArray summation(env);
  for(int t = 0; t < T_MAX; t++){
    summation.add(IloExpr(env));
    for(int p = 0; p < n_r; p++){
      sum.add(IloExpr(env));
      for(int e = 0; e < E; e++)
	sum[p] += R[p][e][t];
      summation[t] += sum[p];
    }
    c.add(summation[t] <= n_r);
  }
  return;
}

void OutputDroplet(IloModel model, BoolVar3DMatrix Y, BoolVarMatrix M, 
		   BoolVarMatrix X, IloRangeArray c, BoolVar3DMatrix R){

  IloEnv env = model.getEnv();
  for(int p = 0; p < Y.getSize(); p++){
    for(int i = 0; i < n; i++){
      for(int t = 0; t < T_MAX; t++){
	Y[p][i].add(IloBoolVar(env));
	c.add(Y[p][i][t] - M[p][i] - X[i][t] >= -1);
	c.add(Y[p][i][t] - M[p][i] - X[i][t] <=  0);
	c.add(Y[p][i][t] + M[p][i] - X[i][t] <=  1);
	c.add(Y[p][i][t] - M[p][i] + X[i][t] <=  1);
      }
    }
  }

  //Droplet back and forth
   for(int t = 0; t < T_MAX; t++){
    for(int e = 0; e < E; e++){
      IloExprArray sum1(env);
      IloExprArray sum2(env);
      for(int p = 0; p < n_m; p++){
	sum1.add(IloExpr(env));
        sum2.add(IloExpr(env));
	for(int l = 0; l < n_r; l++){
	  sum1[p] += R[l][e][t];
	}
	for(int i = 0; i < n; i++){
	  sum2[p] += Y[p][i][t];
	}
	c.add(sum1[p] - sum2[p] + M[p][e] <=  1);
	//c.add(sum1[p] - sum2[p] - M[p][e] >= -1);
      }
    }
   }
  return;
}
