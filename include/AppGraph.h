#ifndef APPGRAPH_H
#define APPGRAPH_H

#include <iostream>                      
#include <string>										
#include <fstream>							
#include <vector>						
#include <algorithm>                       
#include <utility>                         
#include <map> 
#include <unordered_map>                          

#include "Node.h" 
                           
using namespace std;

class AppGraph{
private:
	vector<Node*> inputs_;
	vector<Node*> outputs_;
    vector<Node*> internals_;

	void AddNode(Node*);
	void AddEdge(Node* start, Node* end, int edge_weight);


    	Node* SearchByName(string, unordered_map <string, Node*>);
    	void InputVolumeConsumeCheck();
    	void InternalsVolumeConsistencyCheck();
    	void InputOutputCheck();
    	pair<Node*, int> MakePair(string output_name, unordered_map <string, Node*> SearchMap);

public:
    	AppGraph (string filename, Node*);
    	vector<Node*> inputs();
    	vector<Node*> internals();
    	vector<Node*> outputs();
    	void PrintInternals();
    	void PrintInputs();
    	void PrintOutputs();
        int CountInternalEdges();
};	

#endif

