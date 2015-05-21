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
	name_ = "default";
  	type_ = Input;
}

Node::Node(string Name, Type optype){                                                                       
    name_ = Name;                                                                                       
    type_ = optype;
}

Node::Node(string name, Type type, vector<pair<Node*, int> >* inputs, vector<pair<Node*, int> >* outputs){  
  	name_ = name;																					   
  	type_ = type;
  	inputs_ = *inputs;
  	outputs_ = *outputs;
}

void Node::InputVolumePopulator(int a){
  	pair<Node*, int> temp(NULL, a);
  	outputs_.push_back(temp);
  	return;
}

string Node::name(){
	return name_;
}

