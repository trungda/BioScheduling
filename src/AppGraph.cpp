#include "AppGraph.h"
#include "Node.h"

#include <iostream>                         
#include <string>							 
#include <fstream>							 
#include <vector>							 
#include <algorithm>                         
#include <utility>                         
#include <map>
using namespace std;

void AppGraph::AddNode(Node* n){            
	switch(n->type()){
		case Input : inputs_.push_back(n);  break;
		case Output: outputs_.push_back(n); break;
		case Mix: internals_.push_back(n); break;
	}
	return;
}

vector<Node*> AppGraph::inputs(){
	return inputs_;
}

vector<Node*> AppGraph::internals(){
	return internals_;
}

vector<Node*> AppGraph::outputs(){
	return outputs_;
}

Node* AppGraph::SearchByName(string input_name){
	int i; 
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

void AppGraph::AddEdge(Node* start, Node* end){

	if(start->type() == Input){
		if(start->outputs().empty()){            //The parser has not seen it yet
			pair<Node*, int> output_info;
			output_info.first = end;
			start->set_outputs(output_info);
			pair<Node*, int> input_info;
			input_info.first = start;
			end->set_inputs(input_info);
			//cout << "yes" << endl;
		}
		else{											//The parser has seen it
			//cout << "Yes " ;
			start->InputPointerPopulator(end);
			pair<Node*, int> input_info (start, start->outputs()[0].second);
			end->set_inputs(input_info);
		}
	}
	return;
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



