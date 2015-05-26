#include "AppGraph.h"
#include "Functions.h"

#include <iostream>                          //cout, cin
#include <string>							 //string class 						
#include <fstream>							 //flie handling
#include <vector>							 //vector class
#include <algorithm>                         //easy-to-use algorithms
#include <utility>                           //pair template
#include <map>                               //using maps
#include "Node.h"
#include <regex>
using namespace std;

int main(){

	map<string, Type> conversion;                    
	conversion["INPUT"] = Input;
	conversion["OUTPUT"] = Output;
	conversion["MIX"] = Mix;

	AppGraph app_graph;
	ifstream inputfile_1("../resources/a2.txt");
    string type_string;
    string name;
    string garbage;
    Type type;
    char ch;
    int flag=1;
    Node var[1000];                                                   //Assuming 1000 is the maximum number of nodes
    int i=0;
    if(inputfile_1.is_open()){                             
		for(i=0; !inputfile_1.eof(); i++){
			inputfile_1 >> name;
			ch = name.at(0);
			if(ch!='#' && ch!='('){
				inputfile_1 >> type_string;
				if(type_string.at(0)=='I'){                           //To keep only "INPUT"
					type_string.resize(5);
				}
				type = conversion[type_string];
				Node n(name, type);
				var[i]= n;
				app_graph.AddNode(var+i);
			}
			else{
				getline(inputfile_1, garbage);
			}
		}
    }


	ifstream inputfile_2("../resources/a2.txt");               
	int volume;
	int inputs_counter=0;
	int internals_counter=0;
	string input_name;
	string output_name;
	string volume_string;
	Node* node_address;
	if(inputfile_2.is_open()){                                        //the second pass-(look for numbers approach)	
		while(!inputfile_2.eof()){
			inputfile_2 >> name;
			ch = name.at(0);

			if(ch!='#'){
				inputfile_2 >> type_string;
				if(type_string.at(0)== 'I'){
					Node* curr = app_graph.inputs()[inputs_counter];
					type_string.erase(0, 6);
					volume = stoi(type_string);
					curr->InputVolumePopulator(volume);
					inputs_counter++;
				}
				else if(type_string.at(0)== 'M'){
					Node* curr = app_graph.internals()[internals_counter]; 
					inputfile_2 >> input_name;
					input_name.erase(0, 1);
					input_name.pop_back(); 
					node_address = app_graph.SearchByName(input_name);
					app_graph.AddEdge(node_address, curr);
					inputfile_2 >> input_name;
					input_name.pop_back();
					node_address = app_graph.SearchByName(input_name);
					app_graph.AddEdge(node_address, curr);

					inputfile_2 >> output_name;
					output_name.erase(0, 1);
					pair<Node*, int> output_info = MakePair(output_name, app_graph);
					curr->set_outputs(output_info);
					pair<Node*, int> input_info(curr, output_info.second);
					output_info.first->set_inputs(input_info);
					ch='a';
					while(output_name.back()!=')'){
						inputfile_2 >> output_name;
						pair<Node*, int> output_info = MakePair(output_name, app_graph);
						curr->set_outputs(output_info);
						pair<Node*, int> input_info(curr, output_info.second);
						output_info.first->set_inputs(input_info);
						i++;
					}
					internals_counter++;
 				}
			}
			else{
				getline(inputfile_2, garbage);
			}
		}
    }
    //cout << app_graph.internals()[6]->outputs()[0].first->name()<< endl;
    app_graph.PrintInternals();
    app_graph.PrintInputs();
    app_graph.PrintOutputs();
	return 0;
}












  
  