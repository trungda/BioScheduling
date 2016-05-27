#include "../../include/AppGraph.h"
#include "../../include/Node.h"
#include "../../include/ChipArch.h"
#include "../../include/CodeGen.h"

using namespace std;

extern map<string, int> start_time;
extern vector<pair<int, int> > edges;

int main(){
	string cppfile;
	string filename;
	cin >> cppfile;

	//Constructs Application Graph Data Structure
	cin >> filename;
	Node nodearray[1000];
	AppGraph app_graph(filename, nodearray);

	//Constructs Chip Architectture Data Structure
	cin >> filename;
	ChipArch chip_arch(filename);

	//Generate CPLEX code in the CPP file
	CodeGen code;
	code.Generate(chip_arch, app_graph, cppfile);
	return 0;
}











  
  
