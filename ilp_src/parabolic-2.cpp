#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>

#include <ilcplex/ilocplex.h>

#define T_MAX 21
#define n 7          //Number of Mixing Operations
#define n_m 4        //Numer of Mixers
#define T 3          //Operation Time
#define E 8          //Edges between mix nodes

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

  c.add(s[1] - s[0] >= T);
  c.add(s[2] - s[0] >= T);
  c.add(s[3] - s[1] >= T);
  c.add(s[4] - s[2] >= T);
  c.add(s[5] - s[3] >= T);
  c.add(s[6] - s[4] >= T);
  c.add(s[7] - s[6] >= 0);
  c.add(s[7] - s[5] >= 0);
}

void CreateSchedulingConstraint(IloModel model, BoolVarMatrix Y, BoolVarMatrix X, 
				IloNumVarArray s, IloRangeArray c){
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
  //In the formulation, the edges are enumerated left to right, bottom to top
  for(int i = 0; i < Y.getSize(); i++){
    sum.add(IloExpr(env));
    for(int t = 0; t < T_MAX; t++){
      Y[i].add(IloBoolVar(env)); 
      sum[i] +=  Y[e][t];
      c.add( t - (s[i] + T) - T_MAX*(Y[e][t]-1)     >= 0);
      c.add(-t +  s[j]      - T_MAX*(Y[e][t]-1) + T >= 1);
    }
    c.add(sum[i] == T);
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


