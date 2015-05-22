#include <iostream>                          //cout, cin
#include <string>							 //string class 						
#include <fstream>							 //flie handling
#include <vector>							 //vector class
#include <algorithm>                         //easy-to-use algorithms
#include <utility>                           //pair template
#include <map>                               //using maps
#include "Node.h"
#include "AppGraph.h"
#include "Functions.h"
#include <regex>
using namespace std;

int main(){
	map<string, Type> conversion;                    
	conversion["INPUT"] = Input;
	conversion["OUTPUT"] = Output;
	conversion["MIX"] = Mix;
	AppGraph app_graph;
	ifstream inputfile("../resources/a2.txt");
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
				/*if(flag){
					name_size = name.size()-1;
					flag = 0;
				}*/
				inputfile_1 >> type_string;
				if(type_string.at(0)=='I'){                           //To keep only "INPUT"
					type_string.resize(5);
				}
				type = conversion[type_string];
				//cout << name << '\t' << optype << endl;             //To check for Correctness
				Node n(name, type);
				var[i]= n;
				app_graph.AddNode(var+i, type);
			}
			else{
				getline(inputfile_1, garbage);
			}
		}
    }
	//Printer(&app_graph);                                            //Prints all the inputs in the graph


	ifstream inputfile_2("../resources/a2.txt");                      //Order of occurence is same so no searching overhead
	int volume;
	int inputs_counter=0;
	int outputs_counter=0;
	int internals_counter=0;
	string input_name;
	node* node_address;
	if(inputfile_2.is_open()){                                        //the second pass-(look for numbers approach)
		while(!inputfile_2.eof()){
			inputfile_2 >> name;
			ch = name.at(0);
			if(ch!='#'){
				inputfile_2 >> type_string;
				if(type_string.at(0)== 'I'){
					type_string.erase(0, 6);
					volume = stoi(type_string);
					//cout << volume << endl;
					app_graph.InVolumePopulator(inputs_counter, volume);
					inputs_counter++;
				}
				if(type_string.at(0)== 'M'){
					inputfile_2 >> input_name;
					input1_name.erase(0, 1);
					input1_name.pop_back(); 

					node_address = app_graph.SearchByName(input_name);
					if(node_address->type = Input){
						
					}
					inputfile_2 >> input_name;
					input_name.pop_back(); 
					
				}

			}
			else{
				getline(inputfile_2, garbage);
			}
		}
    }


	return 0;
}












  
  