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



