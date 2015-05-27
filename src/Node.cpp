#include <iostream>                      
#include <string>										
#include <fstream>							
#include <vector>						
#include <algorithm>                       
#include <utility>                         
#include <map>                           

#include "AppGraph.h"
#include "Functions.h"
#include "Node.h"

using namespace std;

Node::Node(){
	name_ = "default";
  	type_ = Input;
}

Node::Node(string Name, Type optype){                                                                       
    name_ = Name;                                                                                       
    type_ = optype;
}

void Node::set_outputs_volume(int volume){
	if(outputs_.empty()){
  		pair<Node*, int> temp;
  		temp.second = volume;
  		outputs_.push_back(temp);
  		return;
  	}
  	else{
  		int i, volume_sum=0;
  		for(i=0; i< outputs_.size()-1; i++)
  			volume_sum += outputs_.at(i).second;
  		if (volume_sum > volume)
  			cout << "Inconsistency at" << this->name() << endl;
  		else{
  			//Remove the Dummy volume 100
  			outputs_.pop_back();                                 
  			pair<Node*, int> temp;
  			temp.second = volume-volume_sum;
  			outputs_.push_back(temp);
  		}
  		return;
  	}
}

void Node::set_inputs_volume(int index, int volume){
	inputs_.at(index).second = volume;
	return;
}

string Node::name(){
	return name_;
}

Type Node::type(){
	return type_;
}

void Node::set_outputs(pair<Node*, int> output_info){
	outputs_.push_back(output_info);
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

void Node::set_inputs_pointer(Node* input){
	pair<Node*, int> temp;
  	temp.first = input;
  	inputs_.push_back(temp);
  	return;
}

void Node::pop_outputs_volume(){
	outputs_.pop_back();
	return;
}