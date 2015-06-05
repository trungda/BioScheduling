#include <iostream>                      
#include <string>										
#include <fstream>							
#include <vector>						
#include <algorithm>                       
#include <utility>                         
#include <map>  
#include <unordered_set>                         

#include "AppGraph.h"
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

//Checks for even outflow
//Sets the outputs_ for the parents of this node if they are of "Input" type
void Node::ConsistencyCheck(){

	int i;
	
	//volume_sum: total volume flowing out of this node
	int volume_sum = 0;
	
	for(i=0; i<this->outputs().size(); i++)
		volume_sum += this->outputs().at(i).second;

	//To ensure even outflow
	if(volume_sum%2!=0){
		cout << "Volume outflow not even at " << this->name() << "\nIt is: " << volume_sum << endl;
		abort();
	}
	
	pair<Node*, int> output_info (this, volume_sum/2);

	if(this->inputs().at(0).first->type() == Input){
		this->set_inputs_volume (0, volume_sum/2);
		this->inputs().at(0).first->SetInputs(output_info);
	}

	else if(this->inputs().at(0).second != volume_sum/2 && this->inputs().at(0).second != 100 ){
		cout << "Inconsistency at "  << this->inputs().at(0).first->name() <<"\nOutflow to "
		<< this->name() << ' ' << " is not the same as required" << endl;
		abort();
	}

	if(this->inputs().at(1).first->type() == Input){
		this->set_inputs_volume (1, volume_sum/2);
		this->inputs().at(1).first->SetInputs(output_info);
	}

	else if(this->inputs().at(1).second != volume_sum/2 && this->inputs().at(1).second != 100){
		cout << "Inconsistency at " << this->inputs().at(1).first->name() <<"\nOutflow to "
		<< this->name() << ' ' << " is not the same as required" << endl;
		abort();
	}

	return;
}

//Used in second pass-only
//Used only for internal Nodes
void Node::SetInputsPointer(Node* parent){

	//dummy_volume: A pair in the input vector of the "this" node has this
	//              volume only if it was set by this "this" node itself
	const int dummy_volume = 100;

	//Parser visits the "this" node before visiting either of its parents
	//Case: "this" node setting its first input
	//OR
	//Case: "this" node setting its second input	
	if(this->inputs().empty() || (this->inputs().size() == 1 && this->inputs().at(0).second == dummy_volume) ){  
		pair<Node*, int> temp(parent, dummy_volume);
		this->set_inputs(temp);
	}

	//Parser visits the "this" node after both parents have been visited
	//Case: first input != parent
	//AND
	//Case: second input!= parent
	else if(this->inputs().size()==2 && this->inputs()[0].first!= parent && this->inputs()[1].first!= parent){
			cout << "Inconsistency at " << this->name()  << endl;
			abort();
	}

	//Parser visits the "this" node after one of its parents have been visited
	else if(this->inputs().size()==1 && this->inputs().at(0).second != dummy_volume){

		//Case: first input (the only input) != parent
		if(this->inputs().at(0).first != parent){
			pair<Node*, int> temp(parent, dummy_volume);
			this->set_inputs(temp);	
		}
	}
	return;
}

//Used by internal nodes
//Used when parent is of type input
void Node::SetInputs(pair<Node*, int> output_info){

	//dummy_volume to indicate that it has not been visited by parser but by other nodes	
	const int dummy_volume = 100;

	if(this->outputs().empty()){
			this->set_outputs(output_info);
			//Setting dummy_volume to indicate unvisited by the parser
			pair<Node*, int> temp;
			temp.second = dummy_volume;
			this->set_outputs(temp);
	}
	else{
		//Unvisited by parser but visited by other nodes
		if(this->outputs().back().second == dummy_volume){
			this->pop_outputs();
			this->set_outputs(output_info);
			pair<Node*, int> temp;
			temp.second = dummy_volume;
			this->set_outputs(temp);
		}

		//Visited by parser 
		else{
			int volume_left = this->outputs().back().second;

			//Case: Available Volume < Required
			if(volume_left < output_info.second){
				cout << "Volume Inconsistency at " << this->name() << "\nOutflow to "
				<< output_info.first->name() << " is not the same as required" << endl;
				abort();
			}
			else{
				this->pop_outputs();
				this->set_outputs(output_info);
				pair <Node*, int> temp;
				temp.second = volume_left - output_info.second;
				this->set_outputs(temp); 
			}
		}
	}
	return;	
}