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

		c.add(s[1] - s[0] >= T*1);
		c.add(s[2] - s[0] >= T*1);
		c.add(s[4] - s[3] >= T*1);
		c.add(s[5] - s[3] >= T*1);
		c.add(s[6] - s[1] >= T*1);
		c.add(s[7] - s[1] >= T*1);
		c.add(s[8] - s[2] >= T*1);
		c.add(s[9] - s[2] >= T*1);
		c.add(s[11] - s[10] >= T*1);
		c.add(s[8] - s[10] >= T*1);
		c.add(s[9] - s[12] >= T*1);
		c.add(s[13] - s[12] >= T*1);
		c.add(s[15] - s[14] >= T*1);
		c.add(s[16] - s[14] >= T*1);
		c.add(s[17] - s[4] >= T*1);
		c.add(s[18] - s[4] >= T*1);
		c.add(s[19] - s[6] >= T*1);
		c.add(s[20] - s[6] >= T*1);
		c.add(s[21] - s[7] >= T*1);
		c.add(s[16] - s[7] >= T*1);
		c.add(s[21] - s[5] >= T*1);
		c.add(s[22] - s[5] >= T*1);
		c.add(s[23] - s[11] >= T*1);
		c.add(s[24] - s[11] >= T*1);
		c.add(s[22] - s[8] >= T*1);
		c.add(s[25] - s[8] >= T*1);
		c.add(s[26] - s[9] >= T*1);
		c.add(s[27] - s[9] >= T*1);
		c.add(s[25] - s[13] >= T*1);
		c.add(s[28] - s[13] >= T*1);
		c.add(s[29] - s[17] >= T*1);
		c.add(s[28] - s[17] >= T*1);
		c.add(s[30] - s[18] >= T*1);
		c.add(s[31] - s[18] >= T*1);
		c.add(s[32] - s[19] >= T*1);
		c.add(s[33] - s[19] >= T*1);
		c.add(s[34] - s[20] >= T*1);
		c.add(s[35] - s[20] >= T*1);
		c.add(s[36] - s[15] >= T*1);
		c.add(s[37] - s[15] >= T*1);
		c.add(s[38] - s[29] >= T*1);
		c.add(s[39] - s[29] >= T*1);
		c.add(s[40] - s[21] >= T*1);
		c.add(s[41] - s[21] >= T*1);
		c.add(s[42] - s[16] >= T*1);
		c.add(s[43] - s[16] >= T*1);
		c.add(s[34] - s[22] >= T*1);
		c.add(s[38] - s[22] >= T*1);
		c.add(s[44] - s[23] >= T*1);
		c.add(s[45] - s[23] >= T*1);
		c.add(s[46] - s[24] >= T*1);
		c.add(s[47] - s[24] >= T*1);
		c.add(s[35] - s[25] >= T*1);
		c.add(s[44] - s[25] >= T*1);
		c.add(s[37] - s[26] >= T*1);
		c.add(s[45] - s[26] >= T*1);
		c.add(s[48] - s[27] >= T*1);
		c.add(s[49] - s[28] >= T*1);
		c.add(s[50] - s[28] >= T*1);
		c.add(s[41] - s[30] >= T*1);
		c.add(s[46] - s[30] >= T*1);
		c.add(s[48] - s[31] >= T*1);
		c.add(s[51] - s[31] >= T*1);
		c.add(s[52] - s[32] >= T*1);
		c.add(s[39] - s[32] >= T*1);
		c.add(s[53] - s[33] >= T*1);
		c.add(s[54] - s[33] >= T*1);
		c.add(s[55] - s[40] >= T*1);
		c.add(s[47] - s[40] >= T*1);
		c.add(s[56] - s[36] >= T*1);
		c.add(s[57] - s[42] >= T*1);
		c.add(s[58] - s[42] >= T*1);
		c.add(s[52] - s[34] >= T*1);
		c.add(s[59] - s[34] >= T*1);
		c.add(s[57] - s[35] >= T*1);
		c.add(s[60] - s[35] >= T*1);
		c.add(s[58] - s[41] >= T*1);
		c.add(s[61] - s[41] >= T*1);
		c.add(s[60] - s[37] >= T*1);
		c.add(s[62] - s[38] >= T*1);
		c.add(s[63] - s[38] >= T*1);
		c.add(s[53] - s[44] >= T*1);
		c.add(s[54] - s[44] >= T*1);
		c.add(s[62] - s[45] >= T*1);
		c.add(s[64] - s[45] >= T*1);
		c.add(s[56] - s[46] >= T*1);
		c.add(s[59] - s[48] >= T*1);
		c.add(s[65] - s[48] >= T*1);
		c.add(s[63] - s[49] >= T*1);
		c.add(s[61] - s[49] >= T*1);
		c.add(s[64] - s[50] >= T*1);
		c.add(s[66] - s[50] >= T*1);
		c.add(s[65] - s[51] >= T*1);
		c.add(s[n] - s[27] >= 0); //OUTPUT
		c.add(s[n] - s[43] >= 0); //OUTPUT
		c.add(s[n] - s[43] >= 0); //OUTPUT
		c.add(s[n] - s[37] >= 0); //OUTPUT
		c.add(s[n] - s[46] >= 0); //OUTPUT
		c.add(s[n] - s[51] >= 0); //OUTPUT
		c.add(s[n] - s[55] >= 0); //OUTPUT
		c.add(s[n] - s[55] >= 0); //OUTPUT
		c.add(s[n] - s[52] >= 0); //OUTPUT
		c.add(s[n] - s[39] >= 0); //OUTPUT
		c.add(s[n] - s[39] >= 0); //OUTPUT
		c.add(s[n] - s[53] >= 0); //OUTPUT
		c.add(s[n] - s[53] >= 0); //OUTPUT
		c.add(s[n] - s[54] >= 0); //OUTPUT
		c.add(s[n] - s[54] >= 0); //OUTPUT
		c.add(s[n] - s[47] >= 0); //OUTPUT
		c.add(s[n] - s[47] >= 0); //OUTPUT
		c.add(s[n] - s[56] >= 0); //OUTPUT
		c.add(s[n] - s[57] >= 0); //OUTPUT
		c.add(s[n] - s[58] >= 0); //OUTPUT
		c.add(s[n] - s[59] >= 0); //OUTPUT
		c.add(s[n] - s[59] >= 0); //OUTPUT
		c.add(s[n] - s[60] >= 0); //OUTPUT
		c.add(s[n] - s[62] >= 0); //OUTPUT
		c.add(s[n] - s[62] >= 0); //OUTPUT
		c.add(s[n] - s[63] >= 0); //OUTPUT
		c.add(s[n] - s[63] >= 0); //OUTPUT
		c.add(s[n] - s[61] >= 0); //OUTPUT
		c.add(s[n] - s[64] >= 0); //OUTPUT
		c.add(s[n] - s[64] >= 0); //OUTPUT
		c.add(s[n] - s[65] >= 0); //OUTPUT
		c.add(s[n] - s[65] >= 0); //OUTPUT
		c.add(s[n] - s[66] >= 0); //OUTPUT
		c.add(s[n] - s[66] >= 0); //OUTPUT


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
			c.add( t - (s[3] + T) - T_MAX*(Y[3][t]-1)  >= 0);
			c.add(-t +  s[5]      - T_MAX*(Y[3][t]-1)  >= 1);
		}
		c.add(sum2[3] - (s[5]-(s[3]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[4].add(IloBoolVar(env));
			sum2[4] +=  Y[4][t];
			c.add( t - (s[1] + T) - T_MAX*(Y[4][t]-1)  >= 0);
			c.add(-t +  s[6]      - T_MAX*(Y[4][t]-1)  >= 1);
		}
		c.add(sum2[4] - (s[6]-(s[1]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[5].add(IloBoolVar(env));
			sum2[5] +=  Y[5][t];
			c.add( t - (s[1] + T) - T_MAX*(Y[5][t]-1)  >= 0);
			c.add(-t +  s[7]      - T_MAX*(Y[5][t]-1)  >= 1);
		}
		c.add(sum2[5] - (s[7]-(s[1]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[6].add(IloBoolVar(env));
			sum2[6] +=  Y[6][t];
			c.add( t - (s[2] + T) - T_MAX*(Y[6][t]-1)  >= 0);
			c.add(-t +  s[8]      - T_MAX*(Y[6][t]-1)  >= 1);
		}
		c.add(sum2[6] - (s[8]-(s[2]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[7].add(IloBoolVar(env));
			sum2[7] +=  Y[7][t];
			c.add( t - (s[2] + T) - T_MAX*(Y[7][t]-1)  >= 0);
			c.add(-t +  s[9]      - T_MAX*(Y[7][t]-1)  >= 1);
		}
		c.add(sum2[7] - (s[9]-(s[2]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[8].add(IloBoolVar(env));
			sum2[8] +=  Y[8][t];
			c.add( t - (s[10] + T) - T_MAX*(Y[8][t]-1)  >= 0);
			c.add(-t +  s[11]      - T_MAX*(Y[8][t]-1)  >= 1);
		}
		c.add(sum2[8] - (s[11]-(s[10]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[9].add(IloBoolVar(env));
			sum2[9] +=  Y[9][t];
			c.add( t - (s[10] + T) - T_MAX*(Y[9][t]-1)  >= 0);
			c.add(-t +  s[8]      - T_MAX*(Y[9][t]-1)  >= 1);
		}
		c.add(sum2[9] - (s[8]-(s[10]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[10].add(IloBoolVar(env));
			sum2[10] +=  Y[10][t];
			c.add( t - (s[12] + T) - T_MAX*(Y[10][t]-1)  >= 0);
			c.add(-t +  s[9]      - T_MAX*(Y[10][t]-1)  >= 1);
		}
		c.add(sum2[10] - (s[9]-(s[12]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[11].add(IloBoolVar(env));
			sum2[11] +=  Y[11][t];
			c.add( t - (s[12] + T) - T_MAX*(Y[11][t]-1)  >= 0);
			c.add(-t +  s[13]      - T_MAX*(Y[11][t]-1)  >= 1);
		}
		c.add(sum2[11] - (s[13]-(s[12]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[12].add(IloBoolVar(env));
			sum2[12] +=  Y[12][t];
			c.add( t - (s[14] + T) - T_MAX*(Y[12][t]-1)  >= 0);
			c.add(-t +  s[15]      - T_MAX*(Y[12][t]-1)  >= 1);
		}
		c.add(sum2[12] - (s[15]-(s[14]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[13].add(IloBoolVar(env));
			sum2[13] +=  Y[13][t];
			c.add( t - (s[14] + T) - T_MAX*(Y[13][t]-1)  >= 0);
			c.add(-t +  s[16]      - T_MAX*(Y[13][t]-1)  >= 1);
		}
		c.add(sum2[13] - (s[16]-(s[14]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[14].add(IloBoolVar(env));
			sum2[14] +=  Y[14][t];
			c.add( t - (s[4] + T) - T_MAX*(Y[14][t]-1)  >= 0);
			c.add(-t +  s[17]      - T_MAX*(Y[14][t]-1)  >= 1);
		}
		c.add(sum2[14] - (s[17]-(s[4]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[15].add(IloBoolVar(env));
			sum2[15] +=  Y[15][t];
			c.add( t - (s[4] + T) - T_MAX*(Y[15][t]-1)  >= 0);
			c.add(-t +  s[18]      - T_MAX*(Y[15][t]-1)  >= 1);
		}
		c.add(sum2[15] - (s[18]-(s[4]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[16].add(IloBoolVar(env));
			sum2[16] +=  Y[16][t];
			c.add( t - (s[6] + T) - T_MAX*(Y[16][t]-1)  >= 0);
			c.add(-t +  s[19]      - T_MAX*(Y[16][t]-1)  >= 1);
		}
		c.add(sum2[16] - (s[19]-(s[6]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[17].add(IloBoolVar(env));
			sum2[17] +=  Y[17][t];
			c.add( t - (s[6] + T) - T_MAX*(Y[17][t]-1)  >= 0);
			c.add(-t +  s[20]      - T_MAX*(Y[17][t]-1)  >= 1);
		}
		c.add(sum2[17] - (s[20]-(s[6]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[18].add(IloBoolVar(env));
			sum2[18] +=  Y[18][t];
			c.add( t - (s[7] + T) - T_MAX*(Y[18][t]-1)  >= 0);
			c.add(-t +  s[21]      - T_MAX*(Y[18][t]-1)  >= 1);
		}
		c.add(sum2[18] - (s[21]-(s[7]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[19].add(IloBoolVar(env));
			sum2[19] +=  Y[19][t];
			c.add( t - (s[7] + T) - T_MAX*(Y[19][t]-1)  >= 0);
			c.add(-t +  s[16]      - T_MAX*(Y[19][t]-1)  >= 1);
		}
		c.add(sum2[19] - (s[16]-(s[7]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[20].add(IloBoolVar(env));
			sum2[20] +=  Y[20][t];
			c.add( t - (s[5] + T) - T_MAX*(Y[20][t]-1)  >= 0);
			c.add(-t +  s[21]      - T_MAX*(Y[20][t]-1)  >= 1);
		}
		c.add(sum2[20] - (s[21]-(s[5]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[21].add(IloBoolVar(env));
			sum2[21] +=  Y[21][t];
			c.add( t - (s[5] + T) - T_MAX*(Y[21][t]-1)  >= 0);
			c.add(-t +  s[22]      - T_MAX*(Y[21][t]-1)  >= 1);
		}
		c.add(sum2[21] - (s[22]-(s[5]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[22].add(IloBoolVar(env));
			sum2[22] +=  Y[22][t];
			c.add( t - (s[11] + T) - T_MAX*(Y[22][t]-1)  >= 0);
			c.add(-t +  s[23]      - T_MAX*(Y[22][t]-1)  >= 1);
		}
		c.add(sum2[22] - (s[23]-(s[11]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[23].add(IloBoolVar(env));
			sum2[23] +=  Y[23][t];
			c.add( t - (s[11] + T) - T_MAX*(Y[23][t]-1)  >= 0);
			c.add(-t +  s[24]      - T_MAX*(Y[23][t]-1)  >= 1);
		}
		c.add(sum2[23] - (s[24]-(s[11]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[24].add(IloBoolVar(env));
			sum2[24] +=  Y[24][t];
			c.add( t - (s[8] + T) - T_MAX*(Y[24][t]-1)  >= 0);
			c.add(-t +  s[22]      - T_MAX*(Y[24][t]-1)  >= 1);
		}
		c.add(sum2[24] - (s[22]-(s[8]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[25].add(IloBoolVar(env));
			sum2[25] +=  Y[25][t];
			c.add( t - (s[8] + T) - T_MAX*(Y[25][t]-1)  >= 0);
			c.add(-t +  s[25]      - T_MAX*(Y[25][t]-1)  >= 1);
		}
		c.add(sum2[25] - (s[25]-(s[8]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[26].add(IloBoolVar(env));
			sum2[26] +=  Y[26][t];
			c.add( t - (s[9] + T) - T_MAX*(Y[26][t]-1)  >= 0);
			c.add(-t +  s[26]      - T_MAX*(Y[26][t]-1)  >= 1);
		}
		c.add(sum2[26] - (s[26]-(s[9]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[27].add(IloBoolVar(env));
			sum2[27] +=  Y[27][t];
			c.add( t - (s[9] + T) - T_MAX*(Y[27][t]-1)  >= 0);
			c.add(-t +  s[27]      - T_MAX*(Y[27][t]-1)  >= 1);
		}
		c.add(sum2[27] - (s[27]-(s[9]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[28].add(IloBoolVar(env));
			sum2[28] +=  Y[28][t];
			c.add( t - (s[13] + T) - T_MAX*(Y[28][t]-1)  >= 0);
			c.add(-t +  s[25]      - T_MAX*(Y[28][t]-1)  >= 1);
		}
		c.add(sum2[28] - (s[25]-(s[13]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[29].add(IloBoolVar(env));
			sum2[29] +=  Y[29][t];
			c.add( t - (s[13] + T) - T_MAX*(Y[29][t]-1)  >= 0);
			c.add(-t +  s[28]      - T_MAX*(Y[29][t]-1)  >= 1);
		}
		c.add(sum2[29] - (s[28]-(s[13]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[30].add(IloBoolVar(env));
			sum2[30] +=  Y[30][t];
			c.add( t - (s[17] + T) - T_MAX*(Y[30][t]-1)  >= 0);
			c.add(-t +  s[29]      - T_MAX*(Y[30][t]-1)  >= 1);
		}
		c.add(sum2[30] - (s[29]-(s[17]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[31].add(IloBoolVar(env));
			sum2[31] +=  Y[31][t];
			c.add( t - (s[17] + T) - T_MAX*(Y[31][t]-1)  >= 0);
			c.add(-t +  s[28]      - T_MAX*(Y[31][t]-1)  >= 1);
		}
		c.add(sum2[31] - (s[28]-(s[17]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[32].add(IloBoolVar(env));
			sum2[32] +=  Y[32][t];
			c.add( t - (s[18] + T) - T_MAX*(Y[32][t]-1)  >= 0);
			c.add(-t +  s[30]      - T_MAX*(Y[32][t]-1)  >= 1);
		}
		c.add(sum2[32] - (s[30]-(s[18]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[33].add(IloBoolVar(env));
			sum2[33] +=  Y[33][t];
			c.add( t - (s[18] + T) - T_MAX*(Y[33][t]-1)  >= 0);
			c.add(-t +  s[31]      - T_MAX*(Y[33][t]-1)  >= 1);
		}
		c.add(sum2[33] - (s[31]-(s[18]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[34].add(IloBoolVar(env));
			sum2[34] +=  Y[34][t];
			c.add( t - (s[19] + T) - T_MAX*(Y[34][t]-1)  >= 0);
			c.add(-t +  s[32]      - T_MAX*(Y[34][t]-1)  >= 1);
		}
		c.add(sum2[34] - (s[32]-(s[19]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[35].add(IloBoolVar(env));
			sum2[35] +=  Y[35][t];
			c.add( t - (s[19] + T) - T_MAX*(Y[35][t]-1)  >= 0);
			c.add(-t +  s[33]      - T_MAX*(Y[35][t]-1)  >= 1);
		}
		c.add(sum2[35] - (s[33]-(s[19]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[36].add(IloBoolVar(env));
			sum2[36] +=  Y[36][t];
			c.add( t - (s[20] + T) - T_MAX*(Y[36][t]-1)  >= 0);
			c.add(-t +  s[34]      - T_MAX*(Y[36][t]-1)  >= 1);
		}
		c.add(sum2[36] - (s[34]-(s[20]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[37].add(IloBoolVar(env));
			sum2[37] +=  Y[37][t];
			c.add( t - (s[20] + T) - T_MAX*(Y[37][t]-1)  >= 0);
			c.add(-t +  s[35]      - T_MAX*(Y[37][t]-1)  >= 1);
		}
		c.add(sum2[37] - (s[35]-(s[20]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[38].add(IloBoolVar(env));
			sum2[38] +=  Y[38][t];
			c.add( t - (s[15] + T) - T_MAX*(Y[38][t]-1)  >= 0);
			c.add(-t +  s[36]      - T_MAX*(Y[38][t]-1)  >= 1);
		}
		c.add(sum2[38] - (s[36]-(s[15]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[39].add(IloBoolVar(env));
			sum2[39] +=  Y[39][t];
			c.add( t - (s[15] + T) - T_MAX*(Y[39][t]-1)  >= 0);
			c.add(-t +  s[37]      - T_MAX*(Y[39][t]-1)  >= 1);
		}
		c.add(sum2[39] - (s[37]-(s[15]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[40].add(IloBoolVar(env));
			sum2[40] +=  Y[40][t];
			c.add( t - (s[29] + T) - T_MAX*(Y[40][t]-1)  >= 0);
			c.add(-t +  s[38]      - T_MAX*(Y[40][t]-1)  >= 1);
		}
		c.add(sum2[40] - (s[38]-(s[29]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[41].add(IloBoolVar(env));
			sum2[41] +=  Y[41][t];
			c.add( t - (s[29] + T) - T_MAX*(Y[41][t]-1)  >= 0);
			c.add(-t +  s[39]      - T_MAX*(Y[41][t]-1)  >= 1);
		}
		c.add(sum2[41] - (s[39]-(s[29]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[42].add(IloBoolVar(env));
			sum2[42] +=  Y[42][t];
			c.add( t - (s[21] + T) - T_MAX*(Y[42][t]-1)  >= 0);
			c.add(-t +  s[40]      - T_MAX*(Y[42][t]-1)  >= 1);
		}
		c.add(sum2[42] - (s[40]-(s[21]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[43].add(IloBoolVar(env));
			sum2[43] +=  Y[43][t];
			c.add( t - (s[21] + T) - T_MAX*(Y[43][t]-1)  >= 0);
			c.add(-t +  s[41]      - T_MAX*(Y[43][t]-1)  >= 1);
		}
		c.add(sum2[43] - (s[41]-(s[21]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[44].add(IloBoolVar(env));
			sum2[44] +=  Y[44][t];
			c.add( t - (s[16] + T) - T_MAX*(Y[44][t]-1)  >= 0);
			c.add(-t +  s[42]      - T_MAX*(Y[44][t]-1)  >= 1);
		}
		c.add(sum2[44] - (s[42]-(s[16]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[45].add(IloBoolVar(env));
			sum2[45] +=  Y[45][t];
			c.add( t - (s[16] + T) - T_MAX*(Y[45][t]-1)  >= 0);
			c.add(-t +  s[43]      - T_MAX*(Y[45][t]-1)  >= 1);
		}
		c.add(sum2[45] - (s[43]-(s[16]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[46].add(IloBoolVar(env));
			sum2[46] +=  Y[46][t];
			c.add( t - (s[22] + T) - T_MAX*(Y[46][t]-1)  >= 0);
			c.add(-t +  s[34]      - T_MAX*(Y[46][t]-1)  >= 1);
		}
		c.add(sum2[46] - (s[34]-(s[22]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[47].add(IloBoolVar(env));
			sum2[47] +=  Y[47][t];
			c.add( t - (s[22] + T) - T_MAX*(Y[47][t]-1)  >= 0);
			c.add(-t +  s[38]      - T_MAX*(Y[47][t]-1)  >= 1);
		}
		c.add(sum2[47] - (s[38]-(s[22]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[48].add(IloBoolVar(env));
			sum2[48] +=  Y[48][t];
			c.add( t - (s[23] + T) - T_MAX*(Y[48][t]-1)  >= 0);
			c.add(-t +  s[44]      - T_MAX*(Y[48][t]-1)  >= 1);
		}
		c.add(sum2[48] - (s[44]-(s[23]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[49].add(IloBoolVar(env));
			sum2[49] +=  Y[49][t];
			c.add( t - (s[23] + T) - T_MAX*(Y[49][t]-1)  >= 0);
			c.add(-t +  s[45]      - T_MAX*(Y[49][t]-1)  >= 1);
		}
		c.add(sum2[49] - (s[45]-(s[23]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[50].add(IloBoolVar(env));
			sum2[50] +=  Y[50][t];
			c.add( t - (s[24] + T) - T_MAX*(Y[50][t]-1)  >= 0);
			c.add(-t +  s[46]      - T_MAX*(Y[50][t]-1)  >= 1);
		}
		c.add(sum2[50] - (s[46]-(s[24]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[51].add(IloBoolVar(env));
			sum2[51] +=  Y[51][t];
			c.add( t - (s[24] + T) - T_MAX*(Y[51][t]-1)  >= 0);
			c.add(-t +  s[47]      - T_MAX*(Y[51][t]-1)  >= 1);
		}
		c.add(sum2[51] - (s[47]-(s[24]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[52].add(IloBoolVar(env));
			sum2[52] +=  Y[52][t];
			c.add( t - (s[25] + T) - T_MAX*(Y[52][t]-1)  >= 0);
			c.add(-t +  s[35]      - T_MAX*(Y[52][t]-1)  >= 1);
		}
		c.add(sum2[52] - (s[35]-(s[25]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[53].add(IloBoolVar(env));
			sum2[53] +=  Y[53][t];
			c.add( t - (s[25] + T) - T_MAX*(Y[53][t]-1)  >= 0);
			c.add(-t +  s[44]      - T_MAX*(Y[53][t]-1)  >= 1);
		}
		c.add(sum2[53] - (s[44]-(s[25]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[54].add(IloBoolVar(env));
			sum2[54] +=  Y[54][t];
			c.add( t - (s[26] + T) - T_MAX*(Y[54][t]-1)  >= 0);
			c.add(-t +  s[37]      - T_MAX*(Y[54][t]-1)  >= 1);
		}
		c.add(sum2[54] - (s[37]-(s[26]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[55].add(IloBoolVar(env));
			sum2[55] +=  Y[55][t];
			c.add( t - (s[26] + T) - T_MAX*(Y[55][t]-1)  >= 0);
			c.add(-t +  s[45]      - T_MAX*(Y[55][t]-1)  >= 1);
		}
		c.add(sum2[55] - (s[45]-(s[26]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[56].add(IloBoolVar(env));
			sum2[56] +=  Y[56][t];
			c.add( t - (s[27] + T) - T_MAX*(Y[56][t]-1)  >= 0);
			c.add(-t +  s[48]      - T_MAX*(Y[56][t]-1)  >= 1);
		}
		c.add(sum2[56] - (s[48]-(s[27]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[57].add(IloBoolVar(env));
			sum2[57] +=  Y[57][t];
			c.add( t - (s[28] + T) - T_MAX*(Y[57][t]-1)  >= 0);
			c.add(-t +  s[49]      - T_MAX*(Y[57][t]-1)  >= 1);
		}
		c.add(sum2[57] - (s[49]-(s[28]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[58].add(IloBoolVar(env));
			sum2[58] +=  Y[58][t];
			c.add( t - (s[28] + T) - T_MAX*(Y[58][t]-1)  >= 0);
			c.add(-t +  s[50]      - T_MAX*(Y[58][t]-1)  >= 1);
		}
		c.add(sum2[58] - (s[50]-(s[28]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[59].add(IloBoolVar(env));
			sum2[59] +=  Y[59][t];
			c.add( t - (s[30] + T) - T_MAX*(Y[59][t]-1)  >= 0);
			c.add(-t +  s[41]      - T_MAX*(Y[59][t]-1)  >= 1);
		}
		c.add(sum2[59] - (s[41]-(s[30]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[60].add(IloBoolVar(env));
			sum2[60] +=  Y[60][t];
			c.add( t - (s[30] + T) - T_MAX*(Y[60][t]-1)  >= 0);
			c.add(-t +  s[46]      - T_MAX*(Y[60][t]-1)  >= 1);
		}
		c.add(sum2[60] - (s[46]-(s[30]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[61].add(IloBoolVar(env));
			sum2[61] +=  Y[61][t];
			c.add( t - (s[31] + T) - T_MAX*(Y[61][t]-1)  >= 0);
			c.add(-t +  s[48]      - T_MAX*(Y[61][t]-1)  >= 1);
		}
		c.add(sum2[61] - (s[48]-(s[31]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[62].add(IloBoolVar(env));
			sum2[62] +=  Y[62][t];
			c.add( t - (s[31] + T) - T_MAX*(Y[62][t]-1)  >= 0);
			c.add(-t +  s[51]      - T_MAX*(Y[62][t]-1)  >= 1);
		}
		c.add(sum2[62] - (s[51]-(s[31]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[63].add(IloBoolVar(env));
			sum2[63] +=  Y[63][t];
			c.add( t - (s[32] + T) - T_MAX*(Y[63][t]-1)  >= 0);
			c.add(-t +  s[52]      - T_MAX*(Y[63][t]-1)  >= 1);
		}
		c.add(sum2[63] - (s[52]-(s[32]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[64].add(IloBoolVar(env));
			sum2[64] +=  Y[64][t];
			c.add( t - (s[32] + T) - T_MAX*(Y[64][t]-1)  >= 0);
			c.add(-t +  s[39]      - T_MAX*(Y[64][t]-1)  >= 1);
		}
		c.add(sum2[64] - (s[39]-(s[32]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[65].add(IloBoolVar(env));
			sum2[65] +=  Y[65][t];
			c.add( t - (s[33] + T) - T_MAX*(Y[65][t]-1)  >= 0);
			c.add(-t +  s[53]      - T_MAX*(Y[65][t]-1)  >= 1);
		}
		c.add(sum2[65] - (s[53]-(s[33]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[66].add(IloBoolVar(env));
			sum2[66] +=  Y[66][t];
			c.add( t - (s[33] + T) - T_MAX*(Y[66][t]-1)  >= 0);
			c.add(-t +  s[54]      - T_MAX*(Y[66][t]-1)  >= 1);
		}
		c.add(sum2[66] - (s[54]-(s[33]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[67].add(IloBoolVar(env));
			sum2[67] +=  Y[67][t];
			c.add( t - (s[40] + T) - T_MAX*(Y[67][t]-1)  >= 0);
			c.add(-t +  s[55]      - T_MAX*(Y[67][t]-1)  >= 1);
		}
		c.add(sum2[67] - (s[55]-(s[40]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[68].add(IloBoolVar(env));
			sum2[68] +=  Y[68][t];
			c.add( t - (s[40] + T) - T_MAX*(Y[68][t]-1)  >= 0);
			c.add(-t +  s[47]      - T_MAX*(Y[68][t]-1)  >= 1);
		}
		c.add(sum2[68] - (s[47]-(s[40]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[69].add(IloBoolVar(env));
			sum2[69] +=  Y[69][t];
			c.add( t - (s[36] + T) - T_MAX*(Y[69][t]-1)  >= 0);
			c.add(-t +  s[56]      - T_MAX*(Y[69][t]-1)  >= 1);
		}
		c.add(sum2[69] - (s[56]-(s[36]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[70].add(IloBoolVar(env));
			sum2[70] +=  Y[70][t];
			c.add( t - (s[42] + T) - T_MAX*(Y[70][t]-1)  >= 0);
			c.add(-t +  s[57]      - T_MAX*(Y[70][t]-1)  >= 1);
		}
		c.add(sum2[70] - (s[57]-(s[42]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[71].add(IloBoolVar(env));
			sum2[71] +=  Y[71][t];
			c.add( t - (s[42] + T) - T_MAX*(Y[71][t]-1)  >= 0);
			c.add(-t +  s[58]      - T_MAX*(Y[71][t]-1)  >= 1);
		}
		c.add(sum2[71] - (s[58]-(s[42]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[72].add(IloBoolVar(env));
			sum2[72] +=  Y[72][t];
			c.add( t - (s[34] + T) - T_MAX*(Y[72][t]-1)  >= 0);
			c.add(-t +  s[52]      - T_MAX*(Y[72][t]-1)  >= 1);
		}
		c.add(sum2[72] - (s[52]-(s[34]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[73].add(IloBoolVar(env));
			sum2[73] +=  Y[73][t];
			c.add( t - (s[34] + T) - T_MAX*(Y[73][t]-1)  >= 0);
			c.add(-t +  s[59]      - T_MAX*(Y[73][t]-1)  >= 1);
		}
		c.add(sum2[73] - (s[59]-(s[34]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[74].add(IloBoolVar(env));
			sum2[74] +=  Y[74][t];
			c.add( t - (s[35] + T) - T_MAX*(Y[74][t]-1)  >= 0);
			c.add(-t +  s[57]      - T_MAX*(Y[74][t]-1)  >= 1);
		}
		c.add(sum2[74] - (s[57]-(s[35]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[75].add(IloBoolVar(env));
			sum2[75] +=  Y[75][t];
			c.add( t - (s[35] + T) - T_MAX*(Y[75][t]-1)  >= 0);
			c.add(-t +  s[60]      - T_MAX*(Y[75][t]-1)  >= 1);
		}
		c.add(sum2[75] - (s[60]-(s[35]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[76].add(IloBoolVar(env));
			sum2[76] +=  Y[76][t];
			c.add( t - (s[41] + T) - T_MAX*(Y[76][t]-1)  >= 0);
			c.add(-t +  s[58]      - T_MAX*(Y[76][t]-1)  >= 1);
		}
		c.add(sum2[76] - (s[58]-(s[41]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[77].add(IloBoolVar(env));
			sum2[77] +=  Y[77][t];
			c.add( t - (s[41] + T) - T_MAX*(Y[77][t]-1)  >= 0);
			c.add(-t +  s[61]      - T_MAX*(Y[77][t]-1)  >= 1);
		}
		c.add(sum2[77] - (s[61]-(s[41]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[78].add(IloBoolVar(env));
			sum2[78] +=  Y[78][t];
			c.add( t - (s[37] + T) - T_MAX*(Y[78][t]-1)  >= 0);
			c.add(-t +  s[60]      - T_MAX*(Y[78][t]-1)  >= 1);
		}
		c.add(sum2[78] - (s[60]-(s[37]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[79].add(IloBoolVar(env));
			sum2[79] +=  Y[79][t];
			c.add( t - (s[38] + T) - T_MAX*(Y[79][t]-1)  >= 0);
			c.add(-t +  s[62]      - T_MAX*(Y[79][t]-1)  >= 1);
		}
		c.add(sum2[79] - (s[62]-(s[38]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[80].add(IloBoolVar(env));
			sum2[80] +=  Y[80][t];
			c.add( t - (s[38] + T) - T_MAX*(Y[80][t]-1)  >= 0);
			c.add(-t +  s[63]      - T_MAX*(Y[80][t]-1)  >= 1);
		}
		c.add(sum2[80] - (s[63]-(s[38]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[81].add(IloBoolVar(env));
			sum2[81] +=  Y[81][t];
			c.add( t - (s[44] + T) - T_MAX*(Y[81][t]-1)  >= 0);
			c.add(-t +  s[53]      - T_MAX*(Y[81][t]-1)  >= 1);
		}
		c.add(sum2[81] - (s[53]-(s[44]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[82].add(IloBoolVar(env));
			sum2[82] +=  Y[82][t];
			c.add( t - (s[44] + T) - T_MAX*(Y[82][t]-1)  >= 0);
			c.add(-t +  s[54]      - T_MAX*(Y[82][t]-1)  >= 1);
		}
		c.add(sum2[82] - (s[54]-(s[44]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[83].add(IloBoolVar(env));
			sum2[83] +=  Y[83][t];
			c.add( t - (s[45] + T) - T_MAX*(Y[83][t]-1)  >= 0);
			c.add(-t +  s[62]      - T_MAX*(Y[83][t]-1)  >= 1);
		}
		c.add(sum2[83] - (s[62]-(s[45]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[84].add(IloBoolVar(env));
			sum2[84] +=  Y[84][t];
			c.add( t - (s[45] + T) - T_MAX*(Y[84][t]-1)  >= 0);
			c.add(-t +  s[64]      - T_MAX*(Y[84][t]-1)  >= 1);
		}
		c.add(sum2[84] - (s[64]-(s[45]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[85].add(IloBoolVar(env));
			sum2[85] +=  Y[85][t];
			c.add( t - (s[46] + T) - T_MAX*(Y[85][t]-1)  >= 0);
			c.add(-t +  s[56]      - T_MAX*(Y[85][t]-1)  >= 1);
		}
		c.add(sum2[85] - (s[56]-(s[46]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[86].add(IloBoolVar(env));
			sum2[86] +=  Y[86][t];
			c.add( t - (s[48] + T) - T_MAX*(Y[86][t]-1)  >= 0);
			c.add(-t +  s[59]      - T_MAX*(Y[86][t]-1)  >= 1);
		}
		c.add(sum2[86] - (s[59]-(s[48]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[87].add(IloBoolVar(env));
			sum2[87] +=  Y[87][t];
			c.add( t - (s[48] + T) - T_MAX*(Y[87][t]-1)  >= 0);
			c.add(-t +  s[65]      - T_MAX*(Y[87][t]-1)  >= 1);
		}
		c.add(sum2[87] - (s[65]-(s[48]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[88].add(IloBoolVar(env));
			sum2[88] +=  Y[88][t];
			c.add( t - (s[49] + T) - T_MAX*(Y[88][t]-1)  >= 0);
			c.add(-t +  s[63]      - T_MAX*(Y[88][t]-1)  >= 1);
		}
		c.add(sum2[88] - (s[63]-(s[49]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[89].add(IloBoolVar(env));
			sum2[89] +=  Y[89][t];
			c.add( t - (s[49] + T) - T_MAX*(Y[89][t]-1)  >= 0);
			c.add(-t +  s[61]      - T_MAX*(Y[89][t]-1)  >= 1);
		}
		c.add(sum2[89] - (s[61]-(s[49]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[90].add(IloBoolVar(env));
			sum2[90] +=  Y[90][t];
			c.add( t - (s[50] + T) - T_MAX*(Y[90][t]-1)  >= 0);
			c.add(-t +  s[64]      - T_MAX*(Y[90][t]-1)  >= 1);
		}
		c.add(sum2[90] - (s[64]-(s[50]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[91].add(IloBoolVar(env));
			sum2[91] +=  Y[91][t];
			c.add( t - (s[50] + T) - T_MAX*(Y[91][t]-1)  >= 0);
			c.add(-t +  s[66]      - T_MAX*(Y[91][t]-1)  >= 1);
		}
		c.add(sum2[91] - (s[66]-(s[50]+T)) == 0);

		sum2.add(IloExpr(env));
		for(int t = 0; t < T_MAX; t++){
			Y[92].add(IloBoolVar(env));
			sum2[92] +=  Y[92][t];
			c.add( t - (s[51] + T) - T_MAX*(Y[92][t]-1)  >= 0);
			c.add(-t +  s[65]      - T_MAX*(Y[92][t]-1)  >= 1);
		}
		c.add(sum2[92] - (s[65]-(s[51]+T)) == 0);

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

		cplex.exportModel("../../model/example.lp");
		cplex.solve();

		env.out() << "Status: " << cplex.getStatus();

		start_time.emplace("O1", 0);
		start_time.emplace("O3", 1);
		start_time.emplace("O4", 2);
		start_time.emplace("O2", 3);
		start_time.emplace("O8", 4);
		start_time.emplace("O11", 5);
		start_time.emplace("O3", 6);
		start_time.emplace("O9", 6);
		start_time.emplace("O10", 7);
		start_time.emplace("O4", 8);
		start_time.emplace("O13", 8);
		start_time.emplace("O14", 9);
		start_time.emplace("O5", 10);
		start_time.emplace("O12", 11);
		start_time.emplace("O13", 12);
		start_time.emplace("O6", 12);
		start_time.emplace("O14", 13);
		start_time.emplace("O15", 13);
		start_time.emplace("O7", 14);
		start_time.emplace("O20", 15);
		start_time.emplace("O23", 16);
		start_time.emplace("O8", 17);
		start_time.emplace("O16", 17);
		start_time.emplace("O17", 18);
		start_time.emplace("O9", 19);
		start_time.emplace("O18", 19);
		start_time.emplace("O19", 20);
		start_time.emplace("O10", 21);
		start_time.emplace("O22", 21);
		start_time.emplace("O23", 22);
		start_time.emplace("O11", 22);
		start_time.emplace("O22", 22);
		start_time.emplace("O24", 22);
		start_time.emplace("O12", 23);
		start_time.emplace("O25", 23);
		start_time.emplace("O26", 24);
		start_time.emplace("O13", 25);
		start_time.emplace("O24", 25);
		start_time.emplace("O27", 25);
		start_time.emplace("O14", 26);
		start_time.emplace("O28", 26);
		start_time.emplace("O29", 27);
		start_time.emplace("O15", 28);
		start_time.emplace("O27", 28);
		start_time.emplace("O30", 28);
		start_time.emplace("O16", 29);
		start_time.emplace("O21", 29);
		start_time.emplace("O30", 30);
		start_time.emplace("O17", 30);
		start_time.emplace("O31", 30);
		start_time.emplace("O32", 31);
		start_time.emplace("O18", 32);
		start_time.emplace("O33", 32);
		start_time.emplace("O34", 33);
		start_time.emplace("O19", 34);
		start_time.emplace("O39", 34);
		start_time.emplace("O40", 35);
		start_time.emplace("O20", 36);
		start_time.emplace("O36", 36);
		start_time.emplace("O42", 37);
		start_time.emplace("O21", 38);
		start_time.emplace("O43", 38);
		start_time.emplace("O53", 39);
		start_time.emplace("O22", 40);
		start_time.emplace("O35", 40);
		start_time.emplace("O41", 41);
		start_time.emplace("O23", 42);
		start_time.emplace("O37", 42);
		start_time.emplace("O38", 43);
		start_time.emplace("O24", 44);
		start_time.emplace("O39", 44);
		start_time.emplace("O43", 44);
		start_time.emplace("O25", 44);
		start_time.emplace("O44", 44);
		start_time.emplace("O45", 45);
		start_time.emplace("O26", 46);
		start_time.emplace("O46", 46);
		start_time.emplace("O56", 47);
		start_time.emplace("O27", 48);
		start_time.emplace("O40", 48);
		start_time.emplace("O44", 48);
		start_time.emplace("O28", 48);
		start_time.emplace("O42", 48);
		start_time.emplace("O45", 48);
		start_time.emplace("O29", 48);
		start_time.emplace("O47", 48);
		start_time.emplace("O30", 49);
		start_time.emplace("O48", 49);
		start_time.emplace("O49", 50);
		start_time.emplace("O31", 51);
		start_time.emplace("O41", 51);
		start_time.emplace("O46", 51);
		start_time.emplace("O32", 51);
		start_time.emplace("O47", 51);
		start_time.emplace("O50", 51);
		start_time.emplace("O33", 52);
		start_time.emplace("O52", 52);
		start_time.emplace("O53", 53);
		start_time.emplace("O34", 53);
		start_time.emplace("O54", 53);
		start_time.emplace("O55", 54);
		start_time.emplace("O35", 55);
		start_time.emplace("O51", 55);
		start_time.emplace("O56", 56);
		start_time.emplace("O36", 56);
		start_time.emplace("O57", 56);
		start_time.emplace("O37", 57);
		start_time.emplace("O58", 57);
		start_time.emplace("O59", 58);
		start_time.emplace("O38", 59);
		start_time.emplace("O39", 59);
		start_time.emplace("O52", 59);
		start_time.emplace("O60", 59);
		start_time.emplace("O40", 60);
		start_time.emplace("O58", 60);
		start_time.emplace("O61", 60);
		start_time.emplace("O41", 61);
		start_time.emplace("O59", 61);
		start_time.emplace("O64", 61);
		start_time.emplace("O42", 62);
		start_time.emplace("O61", 62);
		start_time.emplace("O43", 62);
		start_time.emplace("O62", 62);
		start_time.emplace("O63", 63);
		start_time.emplace("O44", 64);
		start_time.emplace("O54", 64);
		start_time.emplace("O55", 64);
		start_time.emplace("O45", 64);
		start_time.emplace("O62", 64);
		start_time.emplace("O65", 64);
		start_time.emplace("O46", 65);
		start_time.emplace("O57", 65);
		start_time.emplace("O47", 65);
		start_time.emplace("O60", 65);
		start_time.emplace("O66", 65);
		start_time.emplace("O48", 66);
		start_time.emplace("O63", 66);
		start_time.emplace("O64", 66);
		start_time.emplace("O49", 66);
		start_time.emplace("O65", 66);
		start_time.emplace("O67", 66);
		start_time.emplace("O50", 67);
		start_time.emplace("O66", 67);
		start_time.emplace("O51", 67);
		start_time.emplace("O52", 67);
		start_time.emplace("O53", 67);
		start_time.emplace("O54", 67);
		start_time.emplace("O55", 67);
		start_time.emplace("O56", 67);
		start_time.emplace("O57", 67);
		start_time.emplace("O58", 67);
		start_time.emplace("O59", 67);
		start_time.emplace("O60", 67);
		start_time.emplace("O61", 67);
		start_time.emplace("O62", 67);
		start_time.emplace("O63", 67);
		start_time.emplace("O64", 67);
		start_time.emplace("O65", 67);
		start_time.emplace("O66", 67);
		start_time.emplace("O67", 67);

		edge.first = 0;
		edge.second = 1;
		edges.emplace_back(edge);
		edge.second = 2;
		edges.emplace_back(edge);
		edge.first = 3;
		edge.second = 4;
		edges.emplace_back(edge);
		edge.second = 5;
		edges.emplace_back(edge);
		edge.first = 1;
		edge.second = 6;
		edges.emplace_back(edge);
		edge.second = 7;
		edges.emplace_back(edge);
		edge.first = 2;
		edge.second = 8;
		edges.emplace_back(edge);
		edge.second = 9;
		edges.emplace_back(edge);
		edge.first = 10;
		edge.second = 11;
		edges.emplace_back(edge);
		edge.second = 8;
		edges.emplace_back(edge);
		edge.first = 12;
		edge.second = 9;
		edges.emplace_back(edge);
		edge.second = 13;
		edges.emplace_back(edge);
		edge.first = 14;
		edge.second = 15;
		edges.emplace_back(edge);
		edge.second = 16;
		edges.emplace_back(edge);
		edge.first = 4;
		edge.second = 17;
		edges.emplace_back(edge);
		edge.second = 18;
		edges.emplace_back(edge);
		edge.first = 6;
		edge.second = 19;
		edges.emplace_back(edge);
		edge.second = 20;
		edges.emplace_back(edge);
		edge.first = 7;
		edge.second = 21;
		edges.emplace_back(edge);
		edge.second = 16;
		edges.emplace_back(edge);
		edge.first = 5;
		edge.second = 21;
		edges.emplace_back(edge);
		edge.second = 22;
		edges.emplace_back(edge);
		edge.first = 11;
		edge.second = 23;
		edges.emplace_back(edge);
		edge.second = 24;
		edges.emplace_back(edge);
		edge.first = 8;
		edge.second = 22;
		edges.emplace_back(edge);
		edge.second = 25;
		edges.emplace_back(edge);
		edge.first = 9;
		edge.second = 26;
		edges.emplace_back(edge);
		edge.second = 27;
		edges.emplace_back(edge);
		edge.first = 13;
		edge.second = 25;
		edges.emplace_back(edge);
		edge.second = 28;
		edges.emplace_back(edge);
		edge.first = 17;
		edge.second = 29;
		edges.emplace_back(edge);
		edge.second = 28;
		edges.emplace_back(edge);
		edge.first = 18;
		edge.second = 30;
		edges.emplace_back(edge);
		edge.second = 31;
		edges.emplace_back(edge);
		edge.first = 19;
		edge.second = 32;
		edges.emplace_back(edge);
		edge.second = 33;
		edges.emplace_back(edge);
		edge.first = 20;
		edge.second = 34;
		edges.emplace_back(edge);
		edge.second = 35;
		edges.emplace_back(edge);
		edge.first = 15;
		edge.second = 36;
		edges.emplace_back(edge);
		edge.second = 37;
		edges.emplace_back(edge);
		edge.first = 29;
		edge.second = 38;
		edges.emplace_back(edge);
		edge.second = 39;
		edges.emplace_back(edge);
		edge.first = 21;
		edge.second = 40;
		edges.emplace_back(edge);
		edge.second = 41;
		edges.emplace_back(edge);
		edge.first = 16;
		edge.second = 42;
		edges.emplace_back(edge);
		edge.second = 43;
		edges.emplace_back(edge);
		edge.first = 22;
		edge.second = 34;
		edges.emplace_back(edge);
		edge.second = 38;
		edges.emplace_back(edge);
		edge.first = 23;
		edge.second = 44;
		edges.emplace_back(edge);
		edge.second = 45;
		edges.emplace_back(edge);
		edge.first = 24;
		edge.second = 46;
		edges.emplace_back(edge);
		edge.second = 47;
		edges.emplace_back(edge);
		edge.first = 25;
		edge.second = 35;
		edges.emplace_back(edge);
		edge.second = 44;
		edges.emplace_back(edge);
		edge.first = 26;
		edge.second = 37;
		edges.emplace_back(edge);
		edge.second = 45;
		edges.emplace_back(edge);
		edge.first = 27;
		edge.second = 48;
		edges.emplace_back(edge);
		edge.first = 28;
		edge.second = 49;
		edges.emplace_back(edge);
		edge.second = 50;
		edges.emplace_back(edge);
		edge.first = 30;
		edge.second = 41;
		edges.emplace_back(edge);
		edge.second = 46;
		edges.emplace_back(edge);
		edge.first = 31;
		edge.second = 48;
		edges.emplace_back(edge);
		edge.second = 51;
		edges.emplace_back(edge);
		edge.first = 32;
		edge.second = 52;
		edges.emplace_back(edge);
		edge.second = 39;
		edges.emplace_back(edge);
		edge.first = 33;
		edge.second = 53;
		edges.emplace_back(edge);
		edge.second = 54;
		edges.emplace_back(edge);
		edge.first = 40;
		edge.second = 55;
		edges.emplace_back(edge);
		edge.second = 47;
		edges.emplace_back(edge);
		edge.first = 36;
		edge.second = 56;
		edges.emplace_back(edge);
		edge.first = 42;
		edge.second = 57;
		edges.emplace_back(edge);
		edge.second = 58;
		edges.emplace_back(edge);
		edge.first = 43;
		edge.first = 34;
		edge.second = 52;
		edges.emplace_back(edge);
		edge.second = 59;
		edges.emplace_back(edge);
		edge.first = 35;
		edge.second = 57;
		edges.emplace_back(edge);
		edge.second = 60;
		edges.emplace_back(edge);
		edge.first = 41;
		edge.second = 58;
		edges.emplace_back(edge);
		edge.second = 61;
		edges.emplace_back(edge);
		edge.first = 37;
		edge.second = 60;
		edges.emplace_back(edge);
		edge.first = 38;
		edge.second = 62;
		edges.emplace_back(edge);
		edge.second = 63;
		edges.emplace_back(edge);
		edge.first = 44;
		edge.second = 53;
		edges.emplace_back(edge);
		edge.second = 54;
		edges.emplace_back(edge);
		edge.first = 45;
		edge.second = 62;
		edges.emplace_back(edge);
		edge.second = 64;
		edges.emplace_back(edge);
		edge.first = 46;
		edge.second = 56;
		edges.emplace_back(edge);
		edge.first = 48;
		edge.second = 59;
		edges.emplace_back(edge);
		edge.second = 65;
		edges.emplace_back(edge);
		edge.first = 49;
		edge.second = 63;
		edges.emplace_back(edge);
		edge.second = 61;
		edges.emplace_back(edge);
		edge.first = 50;
		edge.second = 64;
		edges.emplace_back(edge);
		edge.second = 66;
		edges.emplace_back(edge);
		edge.first = 51;
		edge.second = 65;
		edges.emplace_back(edge);
		edge.first = 55;
		edge.first = 52;
		edge.first = 39;
		edge.first = 53;
		edge.first = 54;
		edge.first = 47;
		edge.first = 56;
		edge.first = 57;
		edge.first = 58;
		edge.first = 59;
		edge.first = 60;
		edge.first = 62;
		edge.first = 63;
		edge.first = 61;
		edge.first = 64;
		edge.first = 65;
		edge.first = 66;

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
