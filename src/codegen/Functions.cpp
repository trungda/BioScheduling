#include "../../include/Functions.h"
#include "../../include/Directives.h"

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

  // Used n+1 for accomodating an extra variable
  // For being able to write the objective function
  for(int i = 0; i <= n; i++)
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

void PrintResults(IloNumVarArray s, BoolVarMatrix M, BoolVar3DMatrix R, IloCplex cplex){
  map<int, string> start_time_rev;
  map<string, int>::iterator it;
  for(it = start_time.begin(); it != start_time.end(); it++){
    start_time_rev.emplace(it->second, it->first);
  }

  PrintSchedulingResult(s, start_time_rev, cplex);
  PrintMixingBindingResult(M, start_time_rev, cplex);
  PrintStorageBindingResult(R, start_time_rev, cplex);

  return;
}

void PrintSchedulingResult(IloNumVarArray s, map<int, string> start_time_rev, IloCplex cplex){
  vector<double> s_;
  for(int i = 0; i <= n; i++){
    s_.push_back(cplex.getValue(s[i]));
  }

  cout << "\nSCHEDULING RESULTS" << endl;
  map<string, int>::iterator it;
  for(it = start_time.begin(); it != start_time.end(); it++){
    cout << it->first << setw(4) << s_.at(it->second) << endl;
  }
  cout << endl;
  return;
}

void PrintMixingBindingResult(BoolVarMatrix M, map<int, string> start_time_rev, IloCplex cplex){
  double M_[n_m][E];
  for(int i = 0; i < n_m; i++){
    for(int j = 0; j < n; j++)
      M_[i][j] = cplex.getValue(M[i][j]);
  }

  cout << "MIXING BINDING RESULTS" << endl;
  for(int i = 0; i < n_m; i++){
    cout << "Module-" << i << " ";
    for(int j = 0; j < n; j++){
      if(M_[i][j] == 1){
        cout << start_time_rev[j] << " ";
      }
    }
    cout << endl;
  }
  cout << endl;
  return;
}

void PrintStorageBindingResult(BoolVar3DMatrix R, map<int, string> start_time_rev, IloCplex cplex){
  double R_[n_m][E][T_MAX];
  for(int p = 0; p < n_m; p++){
    for(int e = 0; e < E; e++){
      for(int t = 0; t < T_MAX; t++){
        R_[p][e][t] = cplex.getValue(R[p][e][t]);
      }
    }
  }

  cout << "STORAGE BINDING RESULTS" << endl;
  for(int p = 0; p < n_m; p++){
    cout << "Module-" << p << " ";
    for(int e = 0; e < E; e++){
      for(int t = 0; t < T_MAX; t++){
        if(R_[p][e][t] == 1){
          cout << "(" <<start_time_rev[edges.at(e).first] << "-" << start_time_rev[edges.at(e).second] <<  ")" <<":" << t << " ";
        }
      }
    }
    cout << endl;
  }
  cout << endl;
  return;
}

