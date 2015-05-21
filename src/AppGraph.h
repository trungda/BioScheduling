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
		vector<Node*> inputs;
		vector<Node*> outputs;
		vector<Node*> internals;
	public:
		vector<pair<Node*, int> > GetInputs(Node*);                                    
		vector<pair<Node*, int> > GetOutputs(Node*);                                          
		void AddNode(Node*, Type);
		void AddEdge(Node*, Node*);
    	void InVolumePopulator(int index, int volume);
    	vector<Node*> InputAccess();
};	

#endif

