#ifndef APPGRAPH_H
#define APPGRAPH_H
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
		vector<pair<Node*, int> > GetInputs(Node*);                                    
		vector<pair<Node*, int> > GetOutputs(Node*);                                          
		void AddNode(Node*, Type);
		void AddEdge(Node*, Node*);
    	void InVolumePopulator(int index, int volume);
    	node* SearchByName(string);
    	vector<Node*> inputs();
    	vector<Node*> internals();
    	vector<Node*> outputs();
};	

#endif

