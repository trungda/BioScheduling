#include <iostream>                      
#include <string>										
#include <fstream>							
#include <vector>						
#include <algorithm>                       
#include <utility>                         
#include <map>  
#include <unordered_set>                         

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


//Used only in the second-pass of the parser
//Used only for input nodes
void Node::set_outputs_volume(int volume){

	//Case: Parser visits this node before visiting any of its children
	if(outputs_.empty()){
  		pair<Node*, int> temp;
  		temp.second = volume;
  		outputs_.emplace_back(temp);
  	}

  	//Case: Parser visits this node after atleast one of its children have been visited
  	else{
  		int i, volume_sum = 0;

  		//dummy_volume: A flag to signify that this node has not been visited by the parser
  		//once visited, the dummy_volume is removed
  		//const int dummy_volume = 100;

  		//volume_sum: total volume that already visited children are taking from this node
  		//Iterates only till second-last element. Last element contains dummy_volume
  		for(i=0; i< outputs_.size()-1; i++){
  			volume_sum += outputs_.at(i).second;
  		}

  		if (volume_sum > volume){
  			cout << "Inconsistency at " << this->name() <<"\nOutflow > Volume Specified"<< endl;
  			abort();
  		}
  		else{
  			//Remove the dummy_volume
  			outputs_.pop_back();

  			pair<Node*, int> temp;

  			//volume-volume_sum: total volume available for other children (unvisited)
  			temp.second = volume-volume_sum;

  			//Appends the (volume-volume_sum) information for future reference
  			outputs_.emplace_back(temp);
  		}
  	}
  	return;
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
	outputs_.emplace_back(output_info);
	return;
}

vector<pair<Node*, int> > Node::outputs(){
	return outputs_;
}

vector<pair<Node*, int> > Node::inputs(){
	return inputs_;
}

void Node::set_inputs(pair<Node*, int> input_info){
	inputs_.emplace_back(input_info);
	return;
}

int Node::SearchByName(string output_name){
	int i; 
	for(i=0; i<outputs_.size(); i++){
		if(outputs_[i].first->name_ == output_name)
			return i; 
	}
}

void Node::set_inputs_pointer(Node* input){
	pair<Node*, int> temp;
  	temp.first = input;
  	inputs_.emplace_back(temp);
  	return;
}

void Node::pop_outputs(){
	outputs_.pop_back();
	return;
}