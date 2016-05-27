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
	int T_MAX = E*T+5;
	ofstream myfile;
	myfile.open("include/Directives.h", ios::app);
	myfile << "#define n " << n << endl;
	myfile << "#define T_MAX " << T_MAX << endl;
	myfile << "#define E " << E << endl;
	myfile << "\n#endif" << endl;
	myfile.close();
	return;
}

void CodeGen::EdgeInfo(AppGraph app_graph, string & extra_edges){
	int count = 0;
	pair <int, int> edge;
	vector<Node*> internals = app_graph.internals();
	vector<Node*>::iterator i;
	int j;
	pair < map<string, int>::iterator, bool> ret;
	for(i = internals.begin(); i != internals.end(); i++){
		ret = start_time.emplace((*i)->name(), count);	
		map_ = map_ + "\t\tstart_time.emplace(\""+(*i)->name()+"\", "+to_string(count)+");\n";	
		if(ret.second){
			edge.first = count;
			vec_ = vec_ + "\t\tedge.first = "+to_string(count)+";\n"; 
			count ++;
		}
		else{
			edge.first = ret.first->second;
			vec_ = vec_ + "\t\tedge.first = "+to_string(ret.first->second)+";\n";
		}
		for(j = 0; j != (*i)->outputs().size(); j++){
			if((*i)->outputs().at(j).first->type() == Mix){
				ret = start_time.emplace((*i)->outputs().at(j).first->name(), count);
				map_ = map_ + "\t\tstart_time.emplace(\""+(*i)->outputs().at(j).first->name()+"\", "+to_string(count)+");\n";
				if(ret.second){
					edge.second = count;
					vec_ = vec_ + "\t\tedge.second = "+to_string(count)+";\n";
					count ++;
				}
				else{ 
					edge.second = ret.first->second;
					vec_ = vec_ + "\t\tedge.second = "+to_string(ret.first->second)+";\n"; 
				}
				edges.emplace_back(edge);
				vec_ = vec_ + "\t\tedges.emplace_back(edge);\n";
			}
			else{
				if((*i)->outputs().at(j).first->name() != "W"){
					extra_edges = extra_edges + "\t\t" + "c.add(s[n] - s[" + to_string(edge.first) + "] >= 0); //OUTPUT\n";
				}
			}
		}
	}
}

void CodeGen::PrintToSource(string cppfile, string & extra_edges){
	this->PrintBefore(cppfile);
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

	myfile << "map<string, int> start_time;" << endl;
	myfile << "vector<pair<int, int> > edges;" << endl;
	myfile << "pair <int, int> edge;\n" << endl;

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
    
    myfile << map_ << endl;
    myfile << vec_ << endl;
    myfile << "\t\tPrintResults(s, M, R, cplex);" << endl;
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

void CodeGen::Generate(ChipArch chip_arch, AppGraph app_graph, string cppfile){
	this->ChipInfo(chip_arch);
	this->GraphInfo(app_graph, chip_arch);
	string extra_edges;
	this->EdgeInfo(app_graph, extra_edges);
	this->PrintToSource(cppfile, extra_edges);
	return;
}