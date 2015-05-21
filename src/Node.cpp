#include "Node.h"
#include "AppGraph.h"
#include <iostream>                         
#include <string>							 
#include <fstream>							 
#include <vector>							 
#include <algorithm>                         
#include <utility>                         
#include <map>                              
using namespace std;

Node::Node(){
	name = "default";
  	type = Input;
}

Node::Node(string Name, Type optype){                                                                       
    name = Name;                                                                                       
    type = optype;
}

Node::Node(string Name, Type optype, vector<pair<Node*, int> >* iputs, vector<pair<Node*, int> >* oputs){  
  	name = Name;																					   
  	type = optype;
  	inputs = *iputs;
  	outputs = *oputs;
}

void Node::InputVolumePopulator(int a){
  	pair<Node*, int> temp(NULL, a);
  	outputs.push_back(temp);
  	return;
}

