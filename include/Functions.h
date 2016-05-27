#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <iomanip> 

#include <ilcplex/ilocplex.h>

//To use 2-D and 3-D arrays
//Renaming to easier names
typedef IloArray<IloBoolVarArray> BoolVarMatrix;
typedef IloArray<BoolVarMatrix> BoolVar3DMatrix;

/*FUNCTION DEFINITIONS*/

//Generate 2-D and 3-D empty arrays
void Create2DArray(IloModel model, BoolVarMatrix m);
void Create3DArray(IloModel model, BoolVar3DMatrix m, int size);

//To print the results neatly to the console
void PrintResults(IloNumVarArray s, BoolVarMatrix M, BoolVar3DMatrix R, IloCplex cplex);
void PrintSchedulingResult(IloNumVarArray s, map<int, string> start_time_rev, IloCplex cplex);
void PrintMixingBindingResult(BoolVarMatrix M, map<int, string> start_time_rev, IloCplex cplex);
void PrintStorageBindingResult(BoolVar3DMatrix R, map<int, string> start_time_rev, IloCplex cplex);

//To encode the edge relation and objective function
//s: the array of start time variables
//c: the array of constraints
void PopulateFromGraph(IloModel model, IloNumVarArray s, IloRangeArray c); 

//To encode the execution constraints
//To encode the storage constraints
//To encode the resources constraint
//X[i][t]: 2-D array for execution constraints
//Y[e][t]: 2-D array for storage constraints
//s: the array of start time variables
//c: the array of constraints
void CreateSchedulingConstraint(IloModel model, BoolVarMatrix X, BoolVarMatrix Y,
				                IloNumVarArray s, IloRangeArray c);

//To encode mixing binding constraints
//M[p][i]: 2-D array for mixing binding constraints
//X[i][t]: 2-D array for execution constraints
//Y[e][t]: 2-D array for storage constraints
//s: the array of start time variables
//c: the array of constraints
void CreateMixingBindingConstraint(IloModel model, BoolVarMatrix M, BoolVarMatrix Y, 
                                   BoolVarMatrix X, IloNumVarArray s, IloRangeArray c);

//To encode storage binding constraints
//L[p][i][t] = M[p][i] * X[i][t]
//M[p][i]: 2-D array for mixing binding constraints
//X[i][t]: 2-D array for execution constraints
//R[p][e][t]: 3-D array for mixing binding constraints
//Y[e][t]: 2-D array for storage constraints
//c: the array of constraints
void CreateStorageBindingConstraint(IloModel model, BoolVar3DMatrix L, BoolVarMatrix M, 
			                        BoolVarMatrix X, BoolVar3DMatrix R, BoolVarMatrix Y, 
			                        IloRangeArray c);

#endif