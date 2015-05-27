#include <iostream>                      
#include <string>										
#include <fstream>							
#include <vector>						
#include <algorithm>                       
#include <utility>                         
#include <map>                           

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

    string type_string, name;
    string garbage;
    Type type;
    char ch;
    int i;
    Node createnode[1000];                                                

    //First-Padd
    if(inputfile_1.is_open()){                             
	    for(i=0; !inputfile_1.eof(); i++){

	    	//Read the Name
			inputfile_1 >> name;
			ch = name.at(0);
			if(ch!='#' && ch!='('){

				//Read the type
				inputfile_1 >> type_string;
				if(type_string.at(0)=='I'){                           
					type_string.resize(5);
				}
				type = conversion[type_string];
				Node temp(name, type);
				createnode[i]= temp;
				app_graph.AddNode(createnode+i);
			}
			else{
				//Skip the line
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

			//Read the name
			inputfile_2 >> name;
			ch = name.at(0);
			if(ch!='#'){

				//Read the line
				inputfile_2 >> type_string;
				if(type_string.at(0)== 'I'){
					curr_address = app_graph.inputs().at(inputs_counter);
					type_string.erase(0, 6);
					volume = stoi(type_string);
					curr_address->set_outputs_volume(volume);
					inputs_counter++;
				}
				else if(type_string.at(0)== 'M'){
					Node* curr_address = app_graph.internals()[internals_counter];

					//First Input
					inputfile_2 >> input_name;
					input_name.erase(0, 1);
					input_name.pop_back(); 
					node_address = app_graph.SearchByName(input_name);
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
						pair<Node*, int> output_info = MakePair(output_name, app_graph);
						app_graph.AddEdge(curr_address, output_info.first, output_info.second);
						i++;
					}
					internals_counter++;
 				}
			}
			else{
				//Skip the line
				getline(inputfile_2, garbage);
			}
		}
    }
    app_graph.PrintInternals();
    app_graph.PrintInputs();
    app_graph.PrintOutputs();
	return 0;
}












  
  