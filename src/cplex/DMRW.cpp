#include "../../include/Functions.h"
#include "../../include/Directives.h"

using namespace std;

IloEnv env;
IloModel model(env);
IloNumVarArray s(env);
IloRangeArray c(env);
IloCplex cplex(model);

map<string, int> start_time;
vector<pair<int, int> > edges;
pair <int, int> edge;

int main(){
	try{
		PopulateFromGraph(model, s, c);

		model.add(IloMinimize(env, s[n]));

		c.add(s[1] - s[0] >= T);
		c.add(s[2] - s[0] >= T);
		c.add(s[4] - s[3] >= T);
		c.add(s[2] - s[1] >= T);
		c.add(s[5] - s[1] >= T);
		c.add(s[6] - s[4] >= T);
		c.add(s[7] - s[4] >= T);
		c.add(s[8] - s[4] >= T);
		c.add(s[5] - s[2] >= T);
		c.add(s[9] - s[2] >= T);
		c.add(s[7] - s[8] >= T);
		c.add(s[9] - s[5] >= T);
		c.add(s[10] - s[5] >= T);
		c.add(s[6] - s[7] >= T);
		c.add(s[11] - s[7] >= T);
		c.add(s[10] - s[9] >= T);
		c.add(s[11] - s[6] >= T);
		c.add(s[n] - s[10] >= 0); //OUTPUT
		c.add(s[n] - s[11] >= 0); //OUTPUT


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
			c.add( t - (s[3] + T) - T_MAX*(Y[2][t]-1)  >= 0);
			c.add(-t +  s[4]      - T_MAX*(Y[2][t]-1)  >= 1);
		}
		c.add(sum2[2] - (s[4]-(s[3]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[3].add(IloBoolVar(env));
			sum2[3] +=  Y[3][t];
			c.add( t - (s[1] + T) - T_MAX*(Y[3][t]-1)  >= 0);
			c.add(-t +  s[2]      - T_MAX*(Y[3][t]-1)  >= 1);
		}
		c.add(sum2[3] - (s[2]-(s[1]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[4].add(IloBoolVar(env));
			sum2[4] +=  Y[4][t];
			c.add( t - (s[1] + T) - T_MAX*(Y[4][t]-1)  >= 0);
			c.add(-t +  s[5]      - T_MAX*(Y[4][t]-1)  >= 1);
		}
		c.add(sum2[4] - (s[5]-(s[1]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[5].add(IloBoolVar(env));
			sum2[5] +=  Y[5][t];
			c.add( t - (s[4] + T) - T_MAX*(Y[5][t]-1)  >= 0);
			c.add(-t +  s[6]      - T_MAX*(Y[5][t]-1)  >= 1);
		}
		c.add(sum2[5] - (s[6]-(s[4]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[6].add(IloBoolVar(env));
			sum2[6] +=  Y[6][t];
			c.add( t - (s[4] + T) - T_MAX*(Y[6][t]-1)  >= 0);
			c.add(-t +  s[7]      - T_MAX*(Y[6][t]-1)  >= 1);
		}
		c.add(sum2[6] - (s[7]-(s[4]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[7].add(IloBoolVar(env));
			sum2[7] +=  Y[7][t];
			c.add( t - (s[4] + T) - T_MAX*(Y[7][t]-1)  >= 0);
			c.add(-t +  s[8]      - T_MAX*(Y[7][t]-1)  >= 1);
		}
		c.add(sum2[7] - (s[8]-(s[4]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[8].add(IloBoolVar(env));
			sum2[8] +=  Y[8][t];
			c.add( t - (s[2] + T) - T_MAX*(Y[8][t]-1)  >= 0);
			c.add(-t +  s[5]      - T_MAX*(Y[8][t]-1)  >= 1);
		}
		c.add(sum2[8] - (s[5]-(s[2]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[9].add(IloBoolVar(env));
			sum2[9] +=  Y[9][t];
			c.add( t - (s[2] + T) - T_MAX*(Y[9][t]-1)  >= 0);
			c.add(-t +  s[9]      - T_MAX*(Y[9][t]-1)  >= 1);
		}
		c.add(sum2[9] - (s[9]-(s[2]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[10].add(IloBoolVar(env));
			sum2[10] +=  Y[10][t];
			c.add( t - (s[8] + T) - T_MAX*(Y[10][t]-1)  >= 0);
			c.add(-t +  s[7]      - T_MAX*(Y[10][t]-1)  >= 1);
		}
		c.add(sum2[10] - (s[7]-(s[8]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[11].add(IloBoolVar(env));
			sum2[11] +=  Y[11][t];
			c.add( t - (s[5] + T) - T_MAX*(Y[11][t]-1)  >= 0);
			c.add(-t +  s[9]      - T_MAX*(Y[11][t]-1)  >= 1);
		}
		c.add(sum2[11] - (s[9]-(s[5]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[12].add(IloBoolVar(env));
			sum2[12] +=  Y[12][t];
			c.add( t - (s[5] + T) - T_MAX*(Y[12][t]-1)  >= 0);
			c.add(-t +  s[10]      - T_MAX*(Y[12][t]-1)  >= 1);
		}
		c.add(sum2[12] - (s[10]-(s[5]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[13].add(IloBoolVar(env));
			sum2[13] +=  Y[13][t];
			c.add( t - (s[7] + T) - T_MAX*(Y[13][t]-1)  >= 0);
			c.add(-t +  s[6]      - T_MAX*(Y[13][t]-1)  >= 1);
		}
		c.add(sum2[13] - (s[6]-(s[7]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[14].add(IloBoolVar(env));
			sum2[14] +=  Y[14][t];
			c.add( t - (s[7] + T) - T_MAX*(Y[14][t]-1)  >= 0);
			c.add(-t +  s[11]      - T_MAX*(Y[14][t]-1)  >= 1);
		}
		c.add(sum2[14] - (s[11]-(s[7]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[15].add(IloBoolVar(env));
			sum2[15] +=  Y[15][t];
			c.add( t - (s[9] + T) - T_MAX*(Y[15][t]-1)  >= 0);
			c.add(-t +  s[10]      - T_MAX*(Y[15][t]-1)  >= 1);
		}
		c.add(sum2[15] - (s[10]-(s[9]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[16].add(IloBoolVar(env));
			sum2[16] +=  Y[16][t];
			c.add( t - (s[6] + T) - T_MAX*(Y[16][t]-1)  >= 0);
			c.add(-t +  s[11]      - T_MAX*(Y[16][t]-1)  >= 1);
		}
		c.add(sum2[16] - (s[11]-(s[6]+T)) == 0);

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

		cplex.exportModel("../../model/DMRW.lp");
		cplex.solve();

		env.out() << "Status: " << cplex.getStatus();

		start_time.emplace("O1", 0);
		start_time.emplace("O3", 1);
		start_time.emplace("O5", 2);
		start_time.emplace("O2", 3);
		start_time.emplace("O4", 4);
		start_time.emplace("O3", 5);
		start_time.emplace("O5", 5);
		start_time.emplace("O7", 5);
		start_time.emplace("O4", 6);
		start_time.emplace("O10", 6);
		start_time.emplace("O8", 7);
		start_time.emplace("O6", 8);
		start_time.emplace("O5", 9);
		start_time.emplace("O7", 9);
		start_time.emplace("O9", 9);
		start_time.emplace("O6", 10);
		start_time.emplace("O8", 10);
		start_time.emplace("O7", 10);
		start_time.emplace("O9", 10);
		start_time.emplace("O11", 10);
		start_time.emplace("O8", 11);
		start_time.emplace("O10", 11);
		start_time.emplace("O12", 11);
		start_time.emplace("O9", 12);
		start_time.emplace("O11", 12);
		start_time.emplace("O10", 12);
		start_time.emplace("O12", 12);
		start_time.emplace("O11", 12);
		start_time.emplace("O12", 12);

		edge.first = 0;
		edge.second = 1;
		edges.emplace_back(edge);
		edge.second = 2;
		edges.emplace_back(edge);
		edge.first = 3;
		edge.second = 4;
		edges.emplace_back(edge);
		edge.first = 1;
		edge.second = 2;
		edges.emplace_back(edge);
		edge.second = 5;
		edges.emplace_back(edge);
		edge.first = 4;
		edge.second = 6;
		edges.emplace_back(edge);
		edge.second = 7;
		edges.emplace_back(edge);
		edge.second = 8;
		edges.emplace_back(edge);
		edge.first = 2;
		edge.second = 5;
		edges.emplace_back(edge);
		edge.second = 9;
		edges.emplace_back(edge);
		edge.first = 8;
		edge.second = 7;
		edges.emplace_back(edge);
		edge.first = 5;
		edge.second = 9;
		edges.emplace_back(edge);
		edge.second = 10;
		edges.emplace_back(edge);
		edge.first = 7;
		edge.second = 6;
		edges.emplace_back(edge);
		edge.second = 11;
		edges.emplace_back(edge);
		edge.first = 9;
		edge.second = 10;
		edges.emplace_back(edge);
		edge.first = 6;
		edge.second = 11;
		edges.emplace_back(edge);
		edge.first = 10;
		edge.first = 11;

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
