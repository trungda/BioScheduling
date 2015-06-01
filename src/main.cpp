#include <iostream>                      
#include <string>										
#include <fstream>							
#include <vector>						
#include <algorithm>                       
#include <utility>                         
#include <map> 
#include <exception>                          

#include "AppGraph.h"
#include "Functions.h"
#include "Node.h"

using namespace std;

int main(){

	map<string, Type> conversion;                    
	conversion["INPUT"] = Input;
	conversion["OUTPUT"] = Output;
	conversion["MIX"] = Mix;

	AppGraph app_graph;

	ifstream inputfile_1("../resources/a2.txt");

    string name, type_string;
    string garbage;
    Type type;
    char ch;
    int i;
    Node createnode[1000];                                                

    //First-Pass
    if(inputfile_1.is_open()){                             
	    for(i=0; !inputfile_1.eof(); i++){

	    	//Reads the Name
			inputfile_1 >> name;

			//Case:end of inputs
			if(name == "#end")
				break;

			ch = name.at(0);

			//Ignores comments i.e. lines beginning with '#'
			//Ignores Input-Output information i.e strings beginning with '('
			if(ch!='#' && ch!='('){

				//Reads the type
				inputfile_1 >> type_string;

				if(type_string.at(0)=='I'){

					//Keeps only "Input"                           
					type_string.resize(5);
				}
				type = conversion[type_string];
				Node temp(name, type);
				createnode[i]= temp;
				app_graph.AddNode(createnode+i);
			}
			else{
				//Skips the line
				getline(inputfile_1, garbage);
			}
		}
    }

    //Second-Pass
	ifstream inputfile_2("../resources/a2.txt");

	string input_name, output_name, volume_string;           
	int inputs_counter=0, internals_counter=0;
	int volume;
	Node* node_address;
	Node* curr_address;

	if(inputfile_2.is_open()){                                    
		while(!inputfile_2.eof()){

			//Reads the name
			inputfile_2 >> name;

			ch = name.at(0);

			//Ignores comments i.e. lines beginning with '#'
			if(ch!='#'){

				//Reads the type
				inputfile_2 >> type_string;

				if(type_string.at(0)== 'I'){
					curr_address = app_graph.inputs().at(inputs_counter);

					//Keeps only the volume-x from INPUT:x
					type_string.erase(0, 6);

					volume = stoi(type_string);

					//Places the volume information in the node
					//Additional functionality explained in the function definition
					curr_address->set_outputs_volume(volume);

					inputs_counter++;
				}
				else if(type_string.at(0)== 'M'){
					Node* curr_address = app_graph.internals()[internals_counter];

					//First Input
					inputfile_2 >> input_name;
					input_name.erase(0, 1);
					input_name.pop_back();

					//Searches for node with the name "input_name"
					//Returns a pointer to that node
					node_address = app_graph.SearchByName(input_name);

					//Places the pointer to the input node in the current node
					//Additional functionaltiy explained in the function definition
					SetInputsPointer(curr_address, node_address);

					//Second Input
					inputfile_2 >> input_name;
					input_name.pop_back();
					node_address = app_graph.SearchByName(input_name);
					SetInputsPointer(curr_address, node_address);

					//First Output
					inputfile_2 >> output_name;
					output_name.erase(0, 1);
					pair<Node*, int> output_info = MakePair(output_name, app_graph);
					app_graph.AddEdge(curr_address, output_info.first, output_info.second);

					//Remaining Outputs
					while(output_name.back()!=')'){
						inputfile_2 >> output_name;

						//MakePair(013:23, app_graph) would return pair<013*, 23>
						pair<Node*, int> output_info = MakePair(output_name, app_graph);

						//Adds edge between the two nodes with the given weight
						//Additional functionaltiy explained in the function definition
						app_graph.AddEdge(curr_address, output_info.first, output_info.second);
					}

					ConsistencyCheck(curr_address);
					internals_counter++;
 				}
			}
			else{
				//Skip the line
				getline(inputfile_2, garbage);
			}
		}
    }

    //To check if all Input volume is consumed
    app_graph.InputVolumeConsumeCheck();

    //To check if the inflow and outflow is same in internal nodes
    app_graph.InternalsVolumeConsistencyCheck();

    //Print Contents of the Application Graph
    app_graph.PrintInputs();
    app_graph.PrintInternals();
    app_graph.PrintOutputs();
	return 0;
}












  
  