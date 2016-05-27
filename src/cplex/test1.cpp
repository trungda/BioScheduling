#include "../../include/Functions.h"
#include "../../include/Directives.h"

using namespace std;

IloEnv env;
IloModel model(env);
IloNumVarArray s(env);
IloRangeArray c(env);
IloCplex cplex(model);

int main(){
	try{
		PopulateFromGraph(model, s, c);

		model.add(IloMinimize(env, s[n]));

		c.add(s[1] - s[0] >= T);
		c.add(s[2] - s[0] >= T);
		c.add(s[3] - s[1] >= T);
		c.add(s[4] - s[1] >= T);
		c.add(s[5] - s[3] >= T);
		c.add(s[2] - s[3] >= T);
		c.add(s[4] - s[5] >= T);
		c.add(s[6] - s[4] >= T);
		c.add(s[7] - s[4] >= T);
		c.add(s[8] - s[2] >= T);
		c.add(s[9] - s[2] >= T);
		c.add(s[10] - s[6] >= T);
		c.add(s[11] - s[8] >= T);
		c.add(s[7] - s[11] >= T);
		c.add(s[9] - s[11] >= T);
		c.add(s[n] - s[6] >= 0); //OUTPUT
		c.add(s[n] - s[8] >= 0); //OUTPUT
		c.add(s[n] - s[10] >= 0); //OUTPUT
		c.add(s[n] - s[7] >= 0); //OUTPUT
		c.add(s[n] - s[9] >= 0); //OUTPUT


		BoolVarMatrix Y(env, E);
		Create2DArray(model, Y);

		IloExprArray sum2(env); 

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[0].add(IloBoolVar(env));
			sum2[0] +=  Y[0][t];
			c.add( t - (s[0] + T) - T_MAX*(Y[0][t]-1)  >= 0);
			c.add(-t +  s[1]      - T_MAX*(Y[0][t]-1)  >= 1);
		}
		c.add(sum2[0] - (s[1]-(s[0]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[1].add(IloBoolVar(env));
			sum2[1] +=  Y[1][t];
			c.add( t - (s[0] + T) - T_MAX*(Y[1][t]-1)  >= 0);
			c.add(-t +  s[2]      - T_MAX*(Y[1][t]-1)  >= 1);
		}
		c.add(sum2[1] - (s[2]-(s[0]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[2].add(IloBoolVar(env));
			sum2[2] +=  Y[2][t];
			c.add( t - (s[1] + T) - T_MAX*(Y[2][t]-1)  >= 0);
			c.add(-t +  s[3]      - T_MAX*(Y[2][t]-1)  >= 1);
		}
		c.add(sum2[2] - (s[3]-(s[1]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[3].add(IloBoolVar(env));
			sum2[3] +=  Y[3][t];
			c.add( t - (s[1] + T) - T_MAX*(Y[3][t]-1)  >= 0);
			c.add(-t +  s[4]      - T_MAX*(Y[3][t]-1)  >= 1);
		}
		c.add(sum2[3] - (s[4]-(s[1]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[4].add(IloBoolVar(env));
			sum2[4] +=  Y[4][t];
			c.add( t - (s[3] + T) - T_MAX*(Y[4][t]-1)  >= 0);
			c.add(-t +  s[5]      - T_MAX*(Y[4][t]-1)  >= 1);
		}
		c.add(sum2[4] - (s[5]-(s[3]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[5].add(IloBoolVar(env));
			sum2[5] +=  Y[5][t];
			c.add( t - (s[3] + T) - T_MAX*(Y[5][t]-1)  >= 0);
			c.add(-t +  s[2]      - T_MAX*(Y[5][t]-1)  >= 1);
		}
		c.add(sum2[5] - (s[2]-(s[3]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[6].add(IloBoolVar(env));
			sum2[6] +=  Y[6][t];
			c.add( t - (s[5] + T) - T_MAX*(Y[6][t]-1)  >= 0);
			c.add(-t +  s[4]      - T_MAX*(Y[6][t]-1)  >= 1);
		}
		c.add(sum2[6] - (s[4]-(s[5]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[7].add(IloBoolVar(env));
			sum2[7] +=  Y[7][t];
			c.add( t - (s[4] + T) - T_MAX*(Y[7][t]-1)  >= 0);
			c.add(-t +  s[6]      - T_MAX*(Y[7][t]-1)  >= 1);
		}
		c.add(sum2[7] - (s[6]-(s[4]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[8].add(IloBoolVar(env));
			sum2[8] +=  Y[8][t];
			c.add( t - (s[4] + T) - T_MAX*(Y[8][t]-1)  >= 0);
			c.add(-t +  s[7]      - T_MAX*(Y[8][t]-1)  >= 1);
		}
		c.add(sum2[8] - (s[7]-(s[4]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[9].add(IloBoolVar(env));
			sum2[9] +=  Y[9][t];
			c.add( t - (s[2] + T) - T_MAX*(Y[9][t]-1)  >= 0);
			c.add(-t +  s[8]      - T_MAX*(Y[9][t]-1)  >= 1);
		}
		c.add(sum2[9] - (s[8]-(s[2]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[10].add(IloBoolVar(env));
			sum2[10] +=  Y[10][t];
			c.add( t - (s[2] + T) - T_MAX*(Y[10][t]-1)  >= 0);
			c.add(-t +  s[9]      - T_MAX*(Y[10][t]-1)  >= 1);
		}
		c.add(sum2[10] - (s[9]-(s[2]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[11].add(IloBoolVar(env));
			sum2[11] +=  Y[11][t];
			c.add( t - (s[6] + T) - T_MAX*(Y[11][t]-1)  >= 0);
			c.add(-t +  s[10]      - T_MAX*(Y[11][t]-1)  >= 1);
		}
		c.add(sum2[11] - (s[10]-(s[6]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[12].add(IloBoolVar(env));
			sum2[12] +=  Y[12][t];
			c.add( t - (s[8] + T) - T_MAX*(Y[12][t]-1)  >= 0);
			c.add(-t +  s[11]      - T_MAX*(Y[12][t]-1)  >= 1);
		}
		c.add(sum2[12] - (s[11]-(s[8]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[13].add(IloBoolVar(env));
			sum2[13] +=  Y[13][t];
			c.add( t - (s[11] + T) - T_MAX*(Y[13][t]-1)  >= 0);
			c.add(-t +  s[7]      - T_MAX*(Y[13][t]-1)  >= 1);
		}
		c.add(sum2[13] - (s[7]-(s[11]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[14].add(IloBoolVar(env));
			sum2[14] +=  Y[14][t];
			c.add( t - (s[11] + T) - T_MAX*(Y[14][t]-1)  >= 0);
			c.add(-t +  s[9]      - T_MAX*(Y[14][t]-1)  >= 1);
		}
		c.add(sum2[14] - (s[9]-(s[11]+T)) == 0);

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

		cplex.exportModel("../../model/test1.lp");
		cplex.solve();

		env.out() << "Status: " << cplex.getStatus();

		PrintResults(s, M, R, cplex);
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
