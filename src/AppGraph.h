#ifndef APPGRAPH_H
#define APPGRAPH_H

#include <iostream>                      
#include <string>										
#include <fstream>							
#include <vector>						
#include <algorithm>                       
#include <utility>                         
#include <map>                          

#include "Node.h" 
                           
using namespace std;

class AppGraph{
	private:
		vector<Node*> inputs_;
		vector<Node*> outputs_;
		vector<Node*> internals_;
	public:
		vector<Node*> inputs();
    	vector<Node*> internals();
    	vector<Node*> outputs();

		void AddNode(Node*);
		void AddEdge(Node* start, Node* end, int edge_weight);

    	vector<pair<Node*, int> > GetInputs(Node*);                                    
		vector<pair<Node*, int> > GetOutputs(Node*);

    	Node* SearchByName(string);
    	void PrintInternals();
    	void PrintInputs();
    	void PrintOutputs();
    	void InputVolumeConsumeCheck();
    	void InternalsVolumeConsistencyCheck();
    	void InputOutputCheck();
	};	

#endif

