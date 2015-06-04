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

Node* AppGraph::SearchByName(string input_name, unordered_map<string, Node*> SearchMap ){
	unordered_map<string, Node*>::iterator got = SearchMap.find(input_name);
	if(got == SearchMap.end()){
		cout << "Invalid ID "<< input_name << endl;
		abort();
	}
	return got->second;
}	

void AppGraph::PrintOutputs(){
	int i;
	int j;
	cout << "Output type\n" << endl;
	cout << "ID\t|" << "\tINPUTS\t\n";	 
	for(i=0; i<outputs_.size(); i++){
		cout << outputs_.at(i)->name() << "\t|\t";
		//Last element contains only volume_left information
		for(j=0; j<outputs_.at(i)->inputs().size(); j++){
			cout << "|" << outputs_.at(i)->inputs().at(j).first->name()<< ":"
			<<  outputs_.at(i)->inputs().at(j).second << "\t|";
		}
		cout << endl;
	}
	cout << endl;
}

void AppGraph::PrintInputs(){
	int i;
	int j;
	cout << "Input type\n" << endl;
	cout << "ID\t|" << "\tOUTPUTS\t\n";	 
	for(i=0; i<inputs_.size(); i++){
		cout << inputs_.at(i)->name() << "\t|\t";
		//Last element contains only volume_left information
		for(j=0; j<inputs_.at(i)->outputs().size()-1; j++){
			cout << "|" << inputs_.at(i)->outputs().at(j).first->name()<< ":"
			<<  inputs_.at(i)->outputs().at(j).second << "\t|";
		}
		cout << endl;
	}
	cout << endl;
}

void AppGraph::PrintInternals(){
	int i;
	int j;
	cout << "Internal type\n" << endl;
	cout << "ID\t|" << "\t\tINPUTS\t\t|\t\tOUTPUTS\n";	 
	for(i=0; i<internals_.size(); i++){
		cout << internals_.at(i)->name() << "\t|\t";
		for(j=0; j<internals_.at(i)->inputs().size(); j++){
			cout << "|" << internals_.at(i)->inputs().at(j).first->name()<< ":"
			<<  internals_.at(i)->inputs().at(j).second << "\t|";
		}
		cout << "\t|\t";
		for(j=0; j<internals_.at(i)->outputs().size(); j++){
			cout << "|" << internals_.at(i)->outputs().at(j).first->name()<< ":"
			<<  internals_.at(i)->outputs().at(j).second << "\t|";
		}
		cout << endl;
	}
	cout << endl;
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

pair<Node*, int> AppGraph::MakePair(string output_name, unordered_map <string, Node*> SearchMap){
	int i;
	string volume_string;
	output_name.pop_back();
	for(i=0; i < output_name.size(); i++){
		if(output_name[i]==':'){
			break;
		}
	}
	volume_string = output_name.substr(i+1, 10);
	int volume = stoi(volume_string);
	output_name = output_name.substr(0, i);
	Node* node_address = this->SearchByName(output_name, SearchMap);
	pair<Node*, int> output_pair(node_address, volume);
	return output_pair;
}