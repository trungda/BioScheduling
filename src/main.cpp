#include <iostream>                          //cout, cin
#include <string>							 //string class 						
#include <fstream>							 //flie handling
#include <vector>							 //vector class
#include <algorithm>                         //easy-to-use algorithms
#include <utility>                           //pair template
#include <map>                               //using maps
using namespace std;

enum Type {Input, Output, Mix};


class Node{
public:
  string name;
  Type type;
  vector<pair<Node*, int> > inputs;
  vector<pair<Node*, int> > outputs;
public:
  Node(string Name, Type optype){                                                                      //Constructor for the 
    name = Name;                                                                                       //first pass
    type = optype;
  }
  Node(string Name, Type optype, vector<pair<Node*, int> >* iputs, vector<pair<Node*, int> >* oputs){  //Constructor for the 
  	name = Name;																					   //second pass
  	type = optype;
  	inputs = *iputs;
  	outputs = *oputs;
  }
};

class AppGraph{
public:
	vector<Node*> inputs;
	vector<Node*> outputs;
	vector<Node*> internals;
public:
	vector<pair<Node*, int> > GetInputs(Node*);                                              //For a particular node in the graph
	vector<pair<Node*, int> > GetOutputs(Node*);
	void AddNode(Node*, Type);
	void AddEdge(Node*, Node*);
};	

void Printer(AppGraph ap){                                                     //Debugger
	cout << "HERE" << endl;
	int i;
	for(i = 0; i < 10; i++ ){
		cout << ap.inputs[i]-> name <<"and"<< endl;
	}
	return; 
}

void AppGraph::AddNode(Node* n, Type t){             
	switch(t){
		case Input : inputs.push_back(n);
		case Output: outputs.push_back(n);
		case Mix: internals.push_back(n); 
	}
	return;
}



Node* createnode(string Name, Type optype){
	Node* temp;
	*temp = Node(Name, optype);
	return temp;  
}

int main(){


	map<string, Type> conversion;                     //Avoid this map in global scope
	conversion["INPUT"] = Input;
	conversion["OUTPUT"] = Output;
	conversion["MIX"] = Mix;

	AppGraph app_graph;

	ifstream inputfile("a2.txt");
    string optype_string;
    string name;
    string garbage;
    Type optype;
    char ch;
    Node* temp;
    if(inputfile.is_open()){                              //the first pass
		while(!inputfile.eof()){
			inputfile >> name;
			ch = name.at(0);
			if(ch!='#' && ch!='(' ){
				inputfile >> optype_string;

				if(optype_string.at(0)=='I')
					optype_string.resize(5);

				optype = conversion[optype_string];
				temp = createnode(name, optype);
				app_graph.AddNode(temp, optype);
			}
			else
				getline(inputfile, garbage);
		}
    }
	Printer(app_graph);

	return 0;
}












  
  