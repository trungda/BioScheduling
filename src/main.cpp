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
	cin >> filename;

	Node createnode[1000];

	//Constructor for the Application Graph
	AppGraph app_graph(filename, createnode);

	//cout << app_graph.internals().size() << endl;
	app_graph.PrintInputs();
	app_graph.PrintOutputs();
   	app_graph.PrintInternals();

	cin >> filename;

	//Constructor for the Application Graph
	ChipArch chip_arch(filename);

	chip_arch.PrintMixers();
	return 0;
}











  
  