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
		case Input : inputs_.push_back(n);  break;
		case Output: outputs_.push_back(n); break;
		case Mix: internals_.push_back(n); break;
	}
	return;
}

void AppGraph::AddEdge(Node* start, Node* end, int edge_weight){
	pair<Node*, int> output_info (end, edge_weight);
	start->set_outputs(output_info);
	pair<Node*, int> input_info(start, edge_weight);
	if(end->inputs().empty())
		end->set_inputs(input_info);
	else if(end->inputs().size()==1){
		if(end->inputs().at(0).first == start)
			end->set_inputs_volume(0, edge_weight);
		else
			end->set_inputs(input_info);
	}
	else if(end->inputs().size() == 2){
		if(end->inputs().at(0).first == start)
			end->set_inputs_volume(0, edge_weight);
		else if(end->inputs().at(1).first == start)
			end->set_inputs_volume(1, edge_weight);
		else{
			cout << "Inconsistency at" << end->name() << endl;
			return;
		}
	}
	else{
		cout << "Inconsistency at" << end->name() << endl;
		return;
	}
	//Checking consistency at inputs
	int i;
	int volume_sum = 0;
	for(i=0; i<start->outputs().size(); i++)
		volume_sum += start->outputs().at(i).second;
	if(!IfEven(volume_sum)){
		cout << "Inconsistency at" << start->name() << endl;
		return;
	}

	output_info.first = start;
	output_info.second = volume_sum/2;

	if(start->inputs().at(0).first->type() == Input)
		SetInputs(start->inputs().at(0).first, output_info);

	if(start->inputs().at(1).first->type() == Input)
		SetInputs(start->inputs().at(1).first, output_info);
}

Node* AppGraph::SearchByName(string input_name){
	int i, j; 
	int found = 0;
	for(i=0; i<inputs_.size(); i++){
		if(inputs_[i]->name() == input_name)
			return inputs_[i]; 
	}
	for(i=0; i<internals_.size(); i++){
		if(internals_[i]->name() == input_name)
			return internals_[i]; 
	}
	for(i=0; i<outputs_.size(); i++){
		if(outputs_[i]->name() == input_name)
			return outputs_[i]; 
	}
}

void AppGraph::PrintOutputs(){
	int i;
	int j;
	for(i=0; i<outputs_.size(); i++){
		cout << outputs_[i]->name() <<'\t' << outputs_[i]->type() << endl;
		cout << "The inputs are: \n";
		for(j=0; j<outputs_[i]->inputs().size(); j++){
			cout << outputs_[i]->inputs()[j].first->name() << ' ' <<  outputs_[i]->inputs()[j].second << endl;
		}
		cout << "The outputs are: \n";
		for(j=0; j<outputs_[i]->outputs().size(); j++){
			cout << outputs_[i]->outputs()[j].first->name()<< ' ' <<  outputs_[i]->outputs()[j].second << endl;
		}
		cout << endl;
	}
}

void AppGraph::PrintInputs(){
	int i;
	int j;
	for(i=0; i<inputs_.size(); i++){
		cout << inputs_[i]->name() <<'\t' << inputs_[i]->type() << endl;
		cout << "The inputs are: \n";
		for(j=0; j<inputs_[i]->inputs().size(); j++){
			cout << inputs_[i]->inputs()[j].first->name() << ' ' <<  inputs_[i]->inputs()[j].second << endl;
		}
		cout << "The outputs are: \n";
		for(j=0; j<inputs_[i]->outputs().size(); j++){
			cout << inputs_[i]->outputs()[j].first->name()<< ' ' <<  inputs_[i]->outputs()[j].second << endl;
		}
		cout << endl;
	}
}

void AppGraph::PrintInternals(){
	int i;
	int j;
	for(i=0; i<internals_.size(); i++){
		cout << internals_[i]->name() <<'\t' << internals_[i]->type() << endl;
		cout << "The inputs are: \n";
		for(j=0; j<internals_[i]->inputs().size(); j++){
			cout << internals_[i]->inputs()[j].first->name() << ' ' <<  internals_[i]->inputs()[j].second << endl;
		}
		cout << "The outputs are: \n";
		for(j=0; j<internals_[i]->outputs().size(); j++){
			cout << internals_[i]->outputs()[j].first->name()<< ' ' <<  internals_[i]->outputs()[j].second << endl;
		}
		cout << endl;
	}
}

