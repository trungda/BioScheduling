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
    string optype_string;
    string name;
    string garbage;
    Type optype;
    char ch;
    Node var[1000];                                                   //Assuming 1000 is the maximum number of nodes
    int i=0;
    if(inputfile.is_open()){                             
		for(i=0; !inputfile.eof(); i++){
			inputfile >> name;
			ch = name.at(0);
			if(ch!='#' && ch!='('){
				inputfile >> optype_string;
				if(optype_string.at(0)=='I'){                         //To keep only "INPUT"
					optype_string.resize(5);
				}
				optype = conversion[optype_string];
				//cout << name << '\t' << optype << endl;             //To check for Correctness
				Node n(name, optype);
				var[i]= n;
				app_graph.AddNode(var+i, optype);
			}
			else{
				getline(inputfile, garbage);
			}
		}
    }
	//Printer(&app_graph);                                            //Prints all the inputs in the graph
    //cout << app_graph->inputs[5]->name << endl; 
    //int i = 0;
    //cout << app_graph->inputs[0]->name << endl;



    //******************************************************************************************************
	ifstream inputfile_2("../resources/a2.txt");  //Order of occurence is same so no searching overhead
	i=0;
	int volume;
	/*string volume;
	inputfile_2 >> volume;
	cout << volume  << endl;*/
	/*if(inputfile_2.is_open()){                              //the second pass-(look for numbers approach)
		while(!inputfile_2.eof()){
			//cout << "here" << endl;
			inputfile_2 >> name;
			ch = name.at(0);
			if(ch!='#'){
				//cout << "Entered" << endl;
				inputfile_2 >> optype_string;
				//cout << volume << endl;
				cout << optype_string.at(0) << ' ' << name << endl;
				if(optype_string.at(0)== 'I'){
					//cout << "Finally" << endl;
					//inputfile_2.ignore(10, '\n');
					//cout << volume << ' ' << i << endl;
					optype_string.erase(0, 6);
					cout << optype_string << endl;
					//app_graph.InVolumePopulator(i, volume);
					i++;
				}

			}
			else{
				getline(inputfile_2, garbage);

				//cout << garbage <<" garbage"<< endl;
				garbage.resize(0);                   //Flushing out the values not needed in this pass
				name.resize(0);
			}
		}
    }*/



	return 0;
}












  
  