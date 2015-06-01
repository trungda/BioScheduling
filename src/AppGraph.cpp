#include <iostream>                      
#include <string>										
#include <fstream>							
#include <vector>						
#include <algorithm>                       
#include <utility>                         
#include <map>                        

#include "AppGraph.h"
#include "Node.h"
#include "Functions.h"

using namespace std;

vector<Node*> AppGraph::inputs(){
	return inputs_;
}

vector<Node*> AppGraph::internals(){
	return internals_;
}

vector<Node*> AppGraph::outputs(){
	return outputs_;
}

void AppGraph::AddNode(Node* n){            
	switch(n->type()){
		case Input : inputs_.emplace_back(n);  break;
		case Output: outputs_.emplace_back(n); break;
		case Mix: internals_.emplace_back(n); break;
	}
	return;
}


//Used only in the second-pass
//Used only for internal nodes
//Parser currently visiting parent
void AppGraph::AddEdge(Node* parent, Node* child, int edge_weight){

	pair<Node*, int> child_info (child, edge_weight);
	parent->set_outputs(child_info);
	pair<Node*, int> parent_info(parent, edge_weight);

	//Parser has not visited child node

	//Case: Parser has not visited the other parent of the child
	if(child->inputs().empty() || child->type() == Output)
		child->set_inputs(parent_info);

	//Case: Parser has visited the other parent of the child
	else if(child->inputs().size()==1)
			child->set_inputs(parent_info);

	//Parser has visited the child node
	else if(child->inputs().size() == 2){

		//Case: First input to the 'child' node is 'parent'
		if(child->inputs().at(0).first == parent)
			
			//Replacing dummy_volume with the actual volume
			child->set_inputs_volume(0, edge_weight);

		//Case: Second input to the 'child' node is 'parent'
		else if(child->inputs().at(1).first == parent)

			//Replacing dummy_volume with the actual volume
			child->set_inputs_volume(1, edge_weight);

		//Case: None of the inputs set by the child node match the parent
		else{
			cout << "Inconsistency at " << child->name() << endl;
			abort();
		}
	}
	return;
}

Node* AppGraph::SearchByName(string input_name){
	int i, j; 
	int found = 0;
	for(i=0; i<inputs_.size(); i++){
		if(inputs_.at(i)->name() == input_name)
			return inputs_.at(i); 
	}
	for(i=0; i<internals_.size(); i++){
		if(internals_.at(i)->name() == input_name)
			return internals_.at(i); 
	}
	for(i=0; i<outputs_.size(); i++){
		if(outputs_.at(i)->name() == input_name)
			return outputs_.at(i); 
	}
}

void AppGraph::PrintOutputs(){
	int i;
	int j;
	for(i=0; i<outputs_.size(); i++){
		cout << outputs_.at(i)->name() <<'\t' << "Output" << endl;
		cout << "The inputs are: \n";
		for(j=0; j<outputs_.at(i)->inputs().size(); j++){
			cout << outputs_.at(i)->inputs().at(j).first->name() << '\t' 
			<<  outputs_.at(i)->inputs().at(j).second << endl;
		}
		cout << "The outputs are: \n";
		for(j=0; j<outputs_.at(i)->outputs().size(); j++){
			cout << outputs_.at(i)->outputs().at(j).first->name()<< '\t' 
			<<  outputs_.at(i)->outputs().at(j).second << endl;
		}
		cout << endl;
	}
}

void AppGraph::PrintInputs(){
	int i;
	int j;
	for(i=0; i<inputs_.size(); i++){
		cout << inputs_.at(i)->name() <<'\t' << "Input" << endl;
		cout << "The inputs are: \n";
		for(j=0; j<inputs_.at(i)->inputs().size(); j++){
			cout << inputs_.at(i)->inputs().at(j).first->name() << '\t' 
			<<  inputs_.at(i)->inputs().at(j).second << endl;
		}
		cout << "The outputs are: \n";

		//Last element contains only volume_left information
		for(j=0; j<inputs_.at(i)->outputs().size()-1; j++){
			cout << inputs_.at(i)->outputs().at(j).first->name()<< '\t' 
			<<  inputs_.at(i)->outputs().at(j).second << endl;
		}
		cout << endl;
	}
}

void AppGraph::PrintInternals(){
	int i;
	int j;
	for(i=0; i<internals_.size(); i++){
		cout << internals_.at(i)->name() <<'\t' << "Mix" << endl;
		cout << "The inputs are: \n";
		for(j=0; j<internals_.at(i)->inputs().size(); j++){
			cout << internals_.at(i)->inputs().at(j).first->name() << '\t' 
			<<  internals_.at(i)->inputs().at(j).second << endl;
		}
		cout << "The outputs are: \n";
		for(j=0; j<internals_.at(i)->outputs().size(); j++){
			cout << internals_.at(i)->outputs().at(j).first->name()<< '\t' 
			<<  internals_.at(i)->outputs().at(j).second << endl;
		}
		cout << endl;
	}
}

void AppGraph::InputVolumeConsumeCheck(){
	int i;
	for(i = 0; i < inputs_.size(); i++){
		if(inputs_.at(i)->outputs().back().second != 0){
			cout << "Unconsumed Volume = " << inputs_.at(i)->outputs().back().second 
			<< " at " << inputs_.at(i)->name() << endl;
			abort();
		}
	}
}

void AppGraph::InternalsVolumeConsistencyCheck(){
	int i;
	int volume_sum;
	int j;
	for(i=0; i < internals_.size(); i++){
		for(j=0, volume_sum=0; j < internals_.at(i)->outputs().size(); j++)
			volume_sum += internals_.at(i)->outputs().at(j).second;
		if(internals_.at(i)->inputs().at(0).second != volume_sum/2 ||
		   internals_.at(i)->inputs().at(1).second != volume_sum/2){
			cout << "Inconsistency at " << internals_.at(i)->name() << 
			" Outflow is not the same is inflow" << endl;
			abort();
		}
	}
}

void AppGraph::InputOutputCheck(){
	if(inputs_.empty()){
		cout << "No Inputs specified\n";
		abort();
	}
	if(outputs_.empty()){
		cout << "No Outputs specified\n";
		abort();
	}
}
