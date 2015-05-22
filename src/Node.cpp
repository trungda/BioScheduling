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

void Node::InputVolumePopulator(int a){
	if(outputs_.empty()){
  		pair<Node*, int> temp;
  		temp.second = a;
  		outputs_.push_back(temp);
  		return;
  	}
  	else
  		
}

string Node::name(){
	return name_;
}

