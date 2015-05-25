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
  	else{
  		outputs_[0].second=a;
  		return;
  	}

}

string Node::name(){
	return name_;
}

Type Node::type(){
	return type_;
}

void Node::set_outputs(pair<Node*, int> output_info){
	inputs_.push_back(output_info);
	return;
}

vector<pair<Node*, int> > Node::outputs(){
	return outputs_;
}

vector<pair<Node*, int> > Node::inputs(){
	return inputs_;
}

void Node::set_inputs(pair<Node*, int> input_info){
	inputs_.push_back(input_info);
	return;
}

int Node::SearchByName(string output_name){
	int i; 
	for(i=0; i<outputs_.size(); i++){
		if(outputs_[i].first->name_ == output_name)
			return i; 
	}
	//else handle the exception
}

void Node::InputPointerPopulator(Node* output){
	outputs_[0].first= output;
	return;
}

