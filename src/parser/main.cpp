#include "../../include/AppGraph.h"
#include "../../include/Node.h"
#include "../../include/ChipArch.h"
#include "../../include/CodeGen.h"

using namespace std;

int main(){
	string cppfile;
	string filename;

	//Reads the desired cpp file name
	cin >> cppfile;

	//Reads input for Application Graph
	cin >> filename;

	Node nodearray[1000];

	//Constructor for the Application Graph
	AppGraph app_graph(filename, nodearray);

	/*app_graph.PrintInputs();
	app_graph.PrintOutputs();
   	app_graph.PrintInternals();*/

   	//Reads input for Chip Architecture
	cin >> filename;

	//Constructor for the Chip Architecture
	ChipArch chip_arch(filename);

	CodeGen code;

	code.ChipInfo(chip_arch);
	code.GraphInfo(app_graph, chip_arch);
	string extra_edges;
	pair< map<string, int>, vector<pair<int, int> > > edgeinfo = code.EdgeInfo(app_graph, extra_edges);
	code.PrintToSource(edgeinfo, cppfile, extra_edges);

	/*chip_arch.PrintMixers();
	chip_arch.PrintHeaters();
	chip_arch.PrintDetectors();
	chip_arch.PrintReservoirs();*/

	return 0;
}











  
  
