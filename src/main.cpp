#include <iostream>                          //cout, cin
#include <string>							 //string class 						
#include <fstream>							 //flie handling
#include <vector>							 //vector class
#include <algorithm>                         //easy-to-use algorithms
#include <utility>                           //pair template
#include <map>                               //using maps
#include "Node.h"
using namespace std;



class AppGraph{
public:  //Temporarily made public
	vector<Node*> inputs;
	vector<Node*> outputs;
	vector<Node*> internals;
public:
	vector<pair<Node*, int> > GetInputs(Node*);                                           //For a particular node in the graph
	vector<pair<Node*, int> > GetOutputs(Node*);                                          //After the second pass
	void AddNode(Node*, Type);
	void AddEdge(Node*, Node*);
	AppGraph* pointer(){
  	return this;
    }
    void InVolumePopulator(int index, int volume){
    	inputs[index]->InputVolumePopulator(volume);
    	return;
    }
};	

/*void Printer(AppGraph* ap){                                                     //Debugger
	//cout << "HERE" << endl;
	int i;
	for(i = 0; i < (ap->internals).size(); i++ ){
		cout << ap->internals[i]-> name << endl;
	}
	return; 
}*/

void AppGraph::AddNode(Node* n, Type t){            
	switch(t){
		case Input : inputs.push_back(n);  /*cout<< inputs[0]->name << " IP" << endl;*/break;
		case Output: outputs.push_back(n); /*cout<< outputs[outputs.size()-1]->name << "OP" << endl;*/ break;
		case Mix: internals.push_back(n); /*cout<< internals[internals.size()-1]->name << "MIX" << endl;*/ break;
	}
	/*for(i=0; i<inputs.size(); i++){
		cout<< inputs[i]->name << endl;
	}
	cout << endl;*/
	return;
}

int main(){


	map<string, Type> conversion;                     //Avoid this map in global scope
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
    Node var[1000];
    int i=0;
    if(inputfile.is_open()){                              //the first pass
		while(!inputfile.eof()){
			inputfile >> name;
			ch = name.at(0);
			if(ch!='#' && ch!='('){
				inputfile >> optype_string;
				//cout << "Here now" << endl;
				if(optype_string.at(0)=='I'){
					optype_string.resize(5);
				}

				optype = conversion[optype_string];
				//cout << "Here now" << endl;
				//cout << name << " " << optype << endl;
				Node n (name, optype);
				var[i]= n;
				//variables[i] = temp;
				//i++;
				//cout << temp.pointer()->type << endl ;
				app_graph.AddNode(var+i, optype);
				//cout << var[i].name << endl;
				i++;
			}
			else{
				getline(inputfile, garbage);
				//cout << garbage << endl;
				garbage.resize(0);                   //Flushing out the values not needed in this pass
				name.resize(0);
			}
		}
    }
	//Printer(app_graph.pointer());
    //cout << app_graph.inputs[5]->name << endl; 
    //int i = 0;
    //cout << app_graph.inputs[0]->name << endl;



    /*****************************************************************************************************************/
	ifstream inputfile_2("../resources/a2.txt");  //Order of occurence is same so no searching overhead
	i=0;
	int volume;
	/*string volume;
	inputfile_2 >> volume;
	cout << volume  << endl;*/
	if(inputfile_2.is_open()){                              //the second pass-(look for numbers approach)
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
    }



	return 0;
}












  
  