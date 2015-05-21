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
    inputs[index]->InputVolumePopulator(volume);
    return;
}

void AppGraph::AddNode(Node* n, Type t){            
	switch(t){
		case Input : inputs.push_back(n);  break;
		case Output: outputs.push_back(n); break;
		case Mix: internals.push_back(n); break;
	}
	return;
}

vector<Node*> AppGraph::InputAccess(){
	return inputs;
}



