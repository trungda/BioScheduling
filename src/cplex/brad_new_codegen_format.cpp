#include <../../include/Functions.h>

#define T_MAX 20
#define n 12         //Number of Mixing Operations
#define n_m 4        //Numer of Modules
#define n_r 2        //Storage capacity of modules
#define T 1          //Operation Time
#define E 15         //Edges between mix nodes

using namespace std;

IloEnv env;
IloModel model(env);
IloNumVarArray s(env);  
IloRangeArray c(env);
IloCplex cplex(model);

int main(){
  try{
    PopulateFromGraph(model, s, c);

    //Added the objective function to the model
    model.add(IloMinimize(env, s[13]));
  
    //To Start Enumeration from 1
    c.add(s[0] == 100);
  
    //Encoding the edge realtion
    //in the form of a constraint    
    c.add(s[2] - s[1] >= T);         
    c.add(s[3] - s[2] >= T);
    c.add(s[4] - s[3] >= T);
    c.add(s[5] - s[4] >= T);
    c.add(s[6] - s[5] >= T);
    c.add(s[5] - s[2] >= T);
    c.add(s[12]- s[3] >= T);
    c.add(s[12]- s[1] >= T);
    c.add(s[10]- s[5] >= T);
    c.add(s[8] - s[6] >= T);
    c.add(s[10]- s[9] >= T);
    c.add(s[9] - s[7] >= T);
    c.add(s[11]- s[9] >= T);
    c.add(s[11]- s[12] >= T);
    c.add(s[7] - s[12]>= T);
  
    //We need s[13] to be able to
    //write the objective funtion
    c.add(s[13]- s[11]>= 0);
    c.add(s[13]- s[10] >= 0);
    c.add(s[13]- s[8] >= 0);

    BoolVarMatrix Y(env, E);
    Create2DArray(model, Y);

    //sum2[e] holds the summation 
    //from eqn-11 for the edge e
    IloExprArray sum2(env);  
  
    sum2.add(IloExpr(env));
    //The for-loop encodes the storage
    //constraints for this edge
    for(int t = 0; t < T_MAX; t++){
     Y[0].add(IloBoolVar(env)); 
      sum2[0] +=  Y[0][t];
      c.add( t - (s[1] + T) - T_MAX*(Y[0][t]-1)  >= 0);
      c.add(-t +  s[2]      - T_MAX*(Y[0][t]-1)  >= 1);
    }
    c.add(sum2[0] - (s[2]-(s[1]+T)) == 0);


    //Edge-2
    sum2.add(IloExpr(env));
    for(int t = 0; t < T_MAX; t++){
      Y[1].add(IloBoolVar(env)); 
      sum2[1] +=  Y[1][t];
      c.add( t - (s[2] + T) - T_MAX*(Y[1][t]-1) >= 0);
      c.add(-t +  s[3]      - T_MAX*(Y[1][t]-1) >= 1);
    }
    c.add(sum2[1] - (s[3]-(s[2]+T)) == 0);
  
    //Edge-3
    sum2.add(IloExpr(env));
    for(int t = 0; t < T_MAX; t++){
      Y[2].add(IloBoolVar(env)); 
      sum2[2] +=  Y[2][t];
      c.add( t - (s[3] + T) - T_MAX*(Y[2][t]-1)  >= 0);
      c.add(-t +  s[4]      - T_MAX*(Y[2][t]-1)  >= 1);
    }
    c.add(sum2[2] - (s[4]-(s[3]+T)) == 0);

    //Edge-4
    sum2.add(IloExpr(env));
    for(int t = 0; t < T_MAX; t++){
      Y[3].add(IloBoolVar(env)); 
      sum2[3] +=  Y[3][t];
      c.add( t - (s[2] + T) - T_MAX*(Y[3][t]-1)  >= 0);
      c.add(-t +  s[5]      - T_MAX*(Y[3][t]-1)  >= 1);
    }
    c.add(sum2[3] - (s[5]-(s[2]+T)) == 0);

    //Edge-5
    sum2.add(IloExpr(env));
    for(int t = 0; t < T_MAX; t++){
      Y[4].add(IloBoolVar(env)); 
      sum2[4] +=  Y[4][t];
      c.add( t - (s[4] + T) - T_MAX*(Y[4][t]-1)  >= 0);
      c.add(-t +  s[5]      - T_MAX*(Y[4][t]-1)  >= 1);
    }
    c.add(sum2[4] - (s[5]-(s[4]+T)) == 0);


    //Edge-6
    sum2.add(IloExpr(env));
    for(int t = 0; t < T_MAX; t++){
      Y[5].add(IloBoolVar(env)); 
      sum2[5] +=  Y[5][t];
      c.add( t - (s[5] + T) - T_MAX*(Y[5][t]-1)  >= 0);
      c.add(-t +  s[6]      - T_MAX*(Y[5][t]-1)  >= 1);
    }
    c.add(sum2[5] - (s[6]-(s[5]+T)) == 0); 


    //Edge-7
    sum2.add(IloExpr(env));
    for(int t = 0; t < T_MAX; t++){
      Y[6].add(IloBoolVar(env)); 
      sum2[6] +=  Y[6][t];
      c.add( t - (s[1] + T) - T_MAX*(Y[6][t]-1)  >= 0);
      c.add(-t +  s[12]      - T_MAX*(Y[6][t]-1)  >= 1);
    }
    c.add(sum2[6] - (s[12]-(s[1]+T)) == 0);

    //Edge-8
    sum2.add(IloExpr(env));
    for(int t = 0; t < T_MAX; t++){
      Y[7].add(IloBoolVar(env)); 
      sum2[7] +=  Y[7][t];
      c.add( t - (s[12] + T) - T_MAX*(Y[7][t]-1)  >= 0);
      c.add(-t +  s[7]      - T_MAX*(Y[7][t]-1)  >= 1);
    }
    c.add(sum2[7] - (s[7]-(s[12]+T)) == 0);
  
    //Edge-9
    sum2.add(IloExpr(env));
    for(int t = 0; t < T_MAX; t++){
      Y[8].add(IloBoolVar(env)); 
      sum2[8] +=  Y[8][t];
      c.add( t - (s[6] + T) - T_MAX*(Y[8][t]-1)  >= 0);
      c.add(-t +  s[8]      - T_MAX*(Y[8][t]-1)  >= 1);
    }
    c.add(sum2[8] - (s[8]-(s[6]+T)) == 0);

    //Edge-10
    sum2.add(IloExpr(env));
    for(int t = 0; t < T_MAX; t++){
      Y[9].add(IloBoolVar(env)); 
      sum2[9] +=  Y[9][t];
      c.add( t - (s[7] + T) - T_MAX*(Y[9][t]-1) >= 0);
      c.add(-t +  s[9]      - T_MAX*(Y[9][t]-1) >= 1);
    }
    c.add(sum2[9] - (s[9]-(s[7]+T)) == 0);

    //Edge-11
    sum2.add(IloExpr(env));
    for(int t = 0; t < T_MAX; t++){
      Y[10].add(IloBoolVar(env)); 
      sum2[10] +=  Y[10][t];
      c.add( t - (s[9] + T) - T_MAX*(Y[10][t]-1)     >= 0);
      c.add(-t +  s[10]     - T_MAX*(Y[10][t]-1)  >= 1);
    }
    c.add(sum2[10] - (s[10]-(s[9]+T)) == 0);

    //Edge-12
    sum2.add(IloExpr(env));
    for(int t = 0; t < T_MAX; t++){
      Y[11].add(IloBoolVar(env)); 
      sum2[11] +=  Y[11][t];
      c.add( t - (s[9] + T) - T_MAX*(Y[11][t]-1)  >= 0);
      c.add(-t +  s[11]     - T_MAX*(Y[11][t]-1)  >= 1);
    }
    c.add(sum2[11] - (s[11]-(s[9]+T)) == 0);

    //Edge-13
    sum2.add(IloExpr(env));
    for(int t = 0; t < T_MAX; t++){
      Y[12].add(IloBoolVar(env)); 
      sum2[12] +=  Y[12][t];
      c.add( t - (s[12] + T) - T_MAX*(Y[12][t]-1)  >= 0);
      c.add(-t +  s[11]     - T_MAX*(Y[12][t]-1)  >= 1);
    }
    c.add(sum2[12] - (s[11]-(s[12]+T)) == 0);

    //Edge-14
    sum2.add(IloExpr(env));
    for(int t = 0; t < T_MAX; t++){
      Y[13].add(IloBoolVar(env)); 
      sum2[13] +=  Y[13][t];
      c.add( t - (s[5] + T) - T_MAX*(Y[13][t]-1)  >= 0);
      c.add(-t +  s[10]     - T_MAX*(Y[13][t]-1)  >= 1);
    }
    c.add(sum2[13] - (s[10]-(s[5]+T)) == 0);

    //Edge-15
    sum2.add(IloExpr(env));
    for(int t = 0; t < T_MAX; t++){
      Y[14].add(IloBoolVar(env)); 
      sum2[14] +=  Y[14][t];
      c.add( t - (s[3] + T) - T_MAX*(Y[14][t]-1)  >= 0);
      c.add(-t +  s[12]     - T_MAX*(Y[14][t]-1)  >= 1);
    }
    c.add(sum2[14] - (s[10]-(s[5]+T)) == 0);

    BoolVarMatrix X(env, n);
    Create2DArray(model, X);
    CreateSchedulingConstraint(model, X, Y, s, c);
  
    BoolVarMatrix M(env, n_m);
    Create2DArray(model, M);
    CreateMixingBindingConstraint(model, M, Y, X, s, c);

    BoolVar3DMatrix L(env, n_m);
    Create3DArray(model, L, n);
    BoolVar3DMatrix R(env, n_m);
    Create3DArray(model, R, E);
    CreateStorageBindingConstraint(model, L,  M, X, R, Y, c); 

    model.add(c);
    
    cplex.exportModel("brad.lp");
    cplex.solve();

    env.out() << "Status: " << cplex.getStatus() << endl;
    
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
  // 1st for being able to start enumeration from 1
  // 2nd for being able to write the objective function
  for(int i = 0; i < n+2; i++)
    s.add(IloNumVar(env));
}

void CreateSchedulingConstraint(IloModel model, BoolVarMatrix X, BoolVarMatrix Y, 
				                        IloNumVarArray s, IloRangeArray c){
  IloEnv env = model.getEnv();

  //sum[i] holds the summation 
  //from eqn-8 for operation i
  IloExprArray sum(env);

  //The for-loop encodes all
  //the execution constraints
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

  //Resources Constraints
  IloExprArray summation1(env);
  IloExprArray summation2(env);
  for(int t = 0; t < T_MAX; t++){
    summation1.add(IloExpr(env));
    summation2.add(IloExpr(env));
    for(int i = 0; i < X.getSize(); i++){
      summation1[t] += X[i][t];
    }
    for(int e = 0; e < Y.getSize(); e++){
      summation2[t] += Y[e][t];
    }
    c.add(n_r*summation1[t] + summation2[t] <= n_m*n_r);
  } 
  
  return;
}

void CreateMixingBindingConstraint(IloModel model, BoolVarMatrix M, BoolVarMatrix Y, 
                                    BoolVarMatrix X, IloNumVarArray s, IloRangeArray c){

  IloEnv env = model.getEnv();

  //sum[i] holds summation from
  //eqn-13 for operation i
  IloExprArray sum1(env);

  //Creating array M[p][i]
  //i is for ith operation
  for(int p = 0; p < M.getSize(); p++){
    for(int i = 0; i < n; i++)
      M[p].add(IloBoolVar(env));
  }

  //Ensuring operation remains bound to the same module
  for(int i = 0; i < n; i++){
    sum1.add(IloExpr(env));
    for(int p = 0; p < n_m; p++){
      sum1[i] += M[p][i];
    }
    c.add(sum1[i] == 1);
  }

  //Two operations running simulateneously  
  //can not be bound to the same module
  for(int p = 0; p < n_m; p++){
    for(int t = 0; t < T_MAX; t++){
      for(int i = 0; i < n; i++){
       for(int j = i+1; j < n; j++){
         c.add(X[i][t] + X[j][t] + M[p][i] + M[p][j] <=  3);
       }
      }
    }
  }

  return;
}

void CreateStorageBindingConstraint(IloModel model, BoolVar3DMatrix L, BoolVarMatrix M, 
			                              BoolVarMatrix X, BoolVar3DMatrix R, BoolVarMatrix Y, 
                                    IloRangeArray c){

  IloEnv env = model.getEnv();

  //The nested for-loops generate L[p][i][t]
  //that is required to linearize equation 16
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

  //Contructing the array R[p][e][t]
  for(int p = 0; p < R.getSize(); p++){
    for(int e = 0; e < E; e++){
      for(int t = 0; t < T_MAX; t++){
	     R[p][e].add(IloBoolVar(env));
      }
    }
  }

  //Encoding the constraint eqn-15
  for(int t = 0; t < T_MAX; t++){
    IloExprArray sum(env);
    for(int e = 0; e < E; e++){
      sum.add(IloExpr(env));
      for(int p = 0; p < n_m; p++){
        sum[e] += R[p][e][t];
      }
      c.add(sum[e] - Y[e][t] == 0);
    }
  }

  //Encoding the constraint eqn-21
  for(int t = 0; t < T_MAX; t++){
    IloExprArray sum1(env);
    IloExprArray sum2(env);
    for(int p = 0; p < n_m; p++){
      sum1.add(IloExpr(env));
      sum2.add(IloExpr(env));
      for(int e = 0; e < E; e++)
        sum1[p] += R[p][e][t];
      for(int i = 0; i < n; i++)
        sum2[p] += L[p][i][t];
      c.add(sum1[p] - n_r*sum2[p] <= 0);
    }
  }

  return;
}


