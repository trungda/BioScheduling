#include "AppGraph.h"
#include <iostream>                         
#include <string>							 
#include <fstream>							 
#include <vector>							 
#include <algorithm>                         
#include <utility>                         
#include <map>
#include "Node.h"
using namespace std;

void AppGraph::InVolumePopulator(int index, int volume){
    inputs_[index]->InputVolumePopulator(volume);
    return;
}

void AppGraph::AddNode(Node* n, Type t){            
	switch(t){
		case Input : inputs_.push_back(n);  break;
		case Output: outputs_.push_back(n); break;
		case Mix: internals_.push_back(n); break;
	}
	return;
}

vector<Node*> AppGraph::inputs(){
	return inputs_;
}

vector<Node*> AppGraph::internals(){
	return internals_;
}

vector<Node*> AppGraph::outputs(){
	return outputs_;
}

Node* AppGraph::SearchByName(string input_name){
	int i; 
	int found = 0;
	for(i=0; i<inputs_.size(); i++){
		if(inputs_[i]->name == input_name)
			return inputs_[i]; 
	}
	for(i=0; i<internals_.size(); i++){
		if(internals_[i]->name == input_name)
			return internals_[i]; 
	}
	for(i=0; i<outputs_.size(); i++){
		if(outputs_[i]->name == input_name)
			return outputs_[i]; 
	}
}



