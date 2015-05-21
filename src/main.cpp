#include <iostream>                          //cout, cin
#include <string>							 //string class 						
#include <fstream>							 //flie handling
#include <vector>							 //vector class
#include <algorithm>                         //easy-to-use algorithms
#include <utility>                           //pair template
#include <map>                               //using maps
#include "Node.h"
#include "AppGraph.h"
using namespace std;


void Printer(AppGraph* ap){                                                     //Debugger
	int i;
	vector<Node*> input = ap->inputs();
	for(i = 0; i < input.size(); i++ ){
		cout << input[i]-> name() << endl;
	}
	return; 
}

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
    Node var[1000];                                                   //Assuming 1000 is the maximum number of nodes
    int i=0;
    if(inputfile.is_open()){                             
		for(i=0; !inputfile.eof(); i++){
			inputfile >> name;
			ch = name.at(0);
			if(ch!='#' && ch!='('){
				inputfile >> type_string;
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
				getline(inputfile, garbage);
			}
		}
    }
	//Printer(&app_graph);                                            //Prints all the inputs in the graph


	ifstream inputfile_2("../resources/a2.txt");                      //Order of occurence is same so no searching overhead
	int volume;
	string volume;
	if(inputfile_2.is_open()){                                        //the second pass-(look for numbers approach)
		for(i=0; !inputfile_2.eof(); ){
			//cout << "here" << endl;
			inputfile_2 >> name;
			ch = name.at(0);
			if(ch!='#'){
				//cout << "Entered" << endl;
				inputfile_2 >> type_string;
				//cout << volume << endl;
				cout << type_string.at(0) << ' ' << name << endl;
				if(type_string.at(0)== 'I'){
					//cout << "Finally" << endl;
					//inputfile_2.ignore(10, '\n');
					//cout << volume << ' ' << i << endl;
					type_string.erase(0, 6);
					cout << type_string << endl;
					//app_graph.InVolumePopulator(i, volume);
					i++;
				}

			}
			else{
				getline(inputfile_2, garbage);
			}
		}
    }



	return 0;
}












  
  