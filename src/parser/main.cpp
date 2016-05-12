#include "../../include/AppGraph.h"
#include "../../include/Node.h"
#include "../../include/ChipArch.h"
#include "../../include/CodeGen.h"

using namespace std;

int main(){
	string filename;

	//Reads input for Application Graph
	cin >> filename;

	Node nodearray[1000];

	//Constructor for the Application Graph
	AppGraph app_graph(filename, nodearray);

	app_graph.PrintInputs();
	app_graph.PrintOutputs();
   	app_graph.PrintInternals();

   	GenerateCode(app_graph)

   	/*
   	//Reads input for Chip Architecture
	cin >> filename;

	//Constructor for the Chip Architecture
	ChipArch chip_arch(filename);

	chip_arch.PrintMixers();
	chip_arch.PrintHeaters();
	chip_arch.PrintDetectors();
	chip_arch.PrintReservoirs();
	*/

	return 0;
}











  
  
