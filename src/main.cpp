#include <iostream>                      
#include <string>					       	
#include <fstream>					       	
#include <vector>						
#include <algorithm>                       
#include <utility>                         
#include <map>  
#include <unordered_map>                      

#include "AppGraph.h"
#include "Node.h"
#include "ChipArch.h"

using namespace std;

int main(){
	string filename;

	//Reads input for Application Graph
	cin >> filename;

	Node createnode[1000];

	//Constructor for the Application Graph
	AppGraph app_graph(filename, createnode);

	app_graph.PrintInputs();
	app_graph.PrintOutputs();
   	app_graph.PrintInternals();

   	//Reads input for Chip Architecture
	cin >> filename;

	//Constructor for the Chip Architecture
	ChipArch chip_arch(filename);

	chip_arch.PrintMixers();
	chip_arch.PrintHeaters();
	chip_arch.PrintDetectors();
	chip_arch.PrintReservoirs();

	return 0;
}











  
  
