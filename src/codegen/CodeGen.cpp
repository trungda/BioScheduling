#include "../../include/CodeGen.h"	

using namespace std;

void CodeGen::ChipInfo(ChipArch chip_arch){
	pair<int, int> info = chip_arch.mixers();
	int n_r = chip_arch.reservoirs();
	ofstream myfile;
	myfile.open("include/Directives.h", ios::trunc);
	myfile << "#ifndef DIRECTIVES_H" << endl;
	myfile << "#define DIRECTIVES_H \n" << endl;
	myfile << "#define n_m " << info.first << endl;
	myfile << "#define n_r " << n_r << endl;
	myfile << "#define T " << info.second << endl;
	myfile.close();
	return;
}

void CodeGen::GraphInfo(AppGraph app_graph, ChipArch chip_arch){
	int T = chip_arch.mixers().second;
	int n = app_graph.internals().size();
	int E = app_graph.CountInternalEdges();
	int T_MAX = E*T+2;
	ofstream myfile;
	myfile.open("include/Directives.h", ios::app);
	myfile << "#define n " << n << endl;
	myfile << "#define T_MAX " << T_MAX << endl;
	myfile << "#define E " << E << endl;
	myfile << "\n#endif" << endl;
	myfile.close();
	return;
}

pair< map<string, int>, vector<pair<int, int> > > CodeGen::EdgeInfo(AppGraph app_graph, string & extra_edges){
	map <string, int> start_time;
	int count = 0;
	vector <pair<int, int> > edges;
	pair <int, int> edge;
	vector<Node*> internals = app_graph.internals();
	vector<Node*>::iterator i;
	int j;
	pair < map<string, int>::iterator, bool> ret;
	pair<map<string, int>, vector<pair<int, int> > > edgeinfo;  
	for(i = internals.begin(); i != internals.end(); i++){
		ret = start_time.emplace((*i)->name(), count);
		if(ret.second){
			edge.first = count;
			count ++;
		}
		else{
			edge.first = ret.first->second;
		}
		for(j = 0; j != (*i)->outputs().size(); j++){
			if((*i)->outputs().at(j).first->type() == Mix){
				ret = start_time.emplace((*i)->outputs().at(j).first->name(), count);
				if(ret.second){
					edge.second = count;
					count ++;
				}
				else{ 
					edge.second = ret.first->second; 
				}
				edges.emplace_back(edge);
			}
			else{
				if((*i)->outputs().at(j).first->name() != "W"){
					extra_edges = extra_edges + "\t\t" + "c.add(s[n] - s[" + to_string(edge.first) + "] >= 0); //OUTPUT\n";
				}
			}
		}
	}
	edgeinfo.first = start_time;
	edgeinfo.second = edges;
	//cout << extra_edges << endl;
	return edgeinfo;
}

void CodeGen::PrintToSource(pair<map<string, int>, vector<pair<int, int> > > edgeinfo, string cppfile, string & extra_edges){
	this->PrintBefore(cppfile);
	map <string, int> start_time = edgeinfo.first;
	vector <pair<int, int> > edges = edgeinfo.second;
	ofstream myfile;
	string filename = "src/cplex/" + cppfile + ".cpp";
	myfile.open(filename, ios::app);
	vector <pair<int, int> >::iterator i;
	for(i = edges.begin(); i != edges.end(); i++){
		myfile << "\t\t" << "c.add(s[" << (*i).second << "] - s[" << (*i).first << "] >= T);" << endl; 
	}

	myfile << extra_edges << endl;

	myfile << "\n\t\tBoolVarMatrix Y(env, E);" << endl;
	myfile << "\t\tCreate2DArray(model, Y);\n" << endl;
	myfile << "\t\tIloExprArray sum2(env); \n" << endl;

	for(i = edges.begin(); i != edges.end(); i++){
			myfile << "\t\tsum2.add(IloExpr(env));" << endl;
			myfile << "\t\tfor(int t = 0; t < T_MAX; t++){" << endl;
			myfile << "\t\t\tY["<< i - edges.begin()<<"].add(IloBoolVar(env));" << endl;
			myfile << "\t\t\tsum2["<< i - edges.begin()<<"] +=  Y["<< i - edges.begin()<<"][t];" << endl;
			myfile << "\t\t\tc.add( t - (s["<<(*i).first<<"] + T) - T_MAX*(Y["<< i - edges.begin()<<"][t]-1)  >= 0);" << endl;
			myfile << "\t\t\tc.add(-t +  s["<<(*i).second<<"]      - T_MAX*(Y["<< i - edges.begin()<<"][t]-1)  >= 1);" << endl;
			myfile << "\t\t}" << endl;
			myfile << "\t\tc.add(sum2["<< i - edges.begin()<<"] - (s["<<(*i).second<<"]-(s["<<(*i).first<<"]+T)) == 0);\n" << endl;
	}
	myfile.close();
	this->PrintAfter(cppfile);
	return;
}

void CodeGen::PrintBefore(string cppfile){
	string filename = "src/cplex/" + cppfile + ".cpp";
	ofstream myfile;
	myfile.open(filename, ios::trunc);
	myfile << "#include \"../../include/Functions.h\"" << endl;
	myfile << "#include \"../../include/Directives.h\"\n" << endl;

	myfile << "using namespace std;\n" << endl;

	myfile << "IloEnv env;" << endl;
	myfile << "IloModel model(env);" << endl;
	myfile << "IloNumVarArray s(env);" << endl;
	myfile << "IloRangeArray c(env);" << endl;
	myfile << "IloCplex cplex(model);\n" << endl;

	myfile << "int main(){" << endl;
	myfile << "\ttry{" << endl;
	myfile << "\t\tPopulateFromGraph(model, s, c);\n" << endl;

	myfile << "\t\tmodel.add(IloMinimize(env, s[n]));\n" << endl;

	myfile.close();
	return;
}

void CodeGen::PrintAfter(string cppfile){
	string filename = "src/cplex/" + cppfile + ".cpp";
	string modelname = "../../model/" + cppfile + ".lp";
	ofstream myfile;
	myfile.open(filename, ios::app);

	myfile << "\t\tBoolVarMatrix X(env, n);" << endl;
    myfile << "\t\tCreate2DArray(model, X);" << endl; 
    myfile << "\t\tCreateSchedulingConstraint(model, X, Y, s, c);\n" << endl;

	myfile << "\t\tBoolVarMatrix M(env, n_m);" << endl;
    myfile << "\t\tCreate2DArray(model, M);" << endl; 
    myfile << "\t\tCreateMixingBindingConstraint(model, M, Y, X, s, c);\n" << endl;

    myfile << "\t\tBoolVar3DMatrix L(env, n_m);" << endl;
    myfile << "\t\tCreate3DArray(model, L, n);" << endl;
    myfile << "\t\tBoolVar3DMatrix R(env, n_m);" << endl;
    myfile << "\t\tCreate3DArray(model, R, E);" << endl;
    myfile << "\t\tCreateStorageBindingConstraint(model, L,  M, X, R, Y, c);\n" << endl;

    myfile << "\t\tmodel.add(c);\n" << endl;
    
    myfile << "\t\tcplex.exportModel(\"" << modelname <<"\");" << endl;
    myfile << "\t\tcplex.solve();\n" << endl;

    myfile << "\t\tenv.out() << \"Status: \" << cplex.getStatus();\n" << endl;
    
  	myfile << "\t} " << endl;
  	myfile << "\tcatch(IloException& e){ " << endl;
    myfile << "\t\tcerr << \"Error: \" << e << endl; " << endl;
  	myfile << "\t} " << endl;
  	myfile << "\tcatch(...){" << endl;
    myfile << "\t\tcerr << \"Unknown\" << endl;" << endl;
  	myfile << "\t}" << endl;
  	myfile << "\tenv.end();" << endl;
  	myfile << "\treturn 0;" << endl;
	myfile << "} " << endl;
	myfile.close();
	return;
}