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

pair<Node*, int> MakePair(string output_name, AppGraph app_graph){
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
	Node* node_address = app_graph.SearchByName(output_name);
	pair<Node*, int> output_pair(node_address, volume);
	return output_pair;
}

void SetInputsPointer(Node* curr, Node* next){

	//Input being set by itself
	//100 used as dummy to indicate self-set
	if(curr->inputs().empty() || curr->inputs().at(0).second == 100){  
		pair<Node*, int> temp(next, 100);
		curr->set_inputs(temp);
	}

	//Both-Inputs set by other nodes
	else if(curr->inputs().size()==2 && curr->inputs()[0].first!= next && curr->inputs()[1].first!= next)
			cout << "Inconsistency at" << curr->name() << endl;

	//Only one input set and that too by other
	else if(curr->inputs().size()==1 && curr->inputs().at(0).second != 100 ){
		if(curr->inputs().at(0).first != next){
			pair<Node*, int> temp(next, 100);
			curr->set_inputs(temp);	
		}
	}

	return;
}

void SetInputs(Node* input, pair<Node*, int> output_info){
	if(input->outputs().empty()){
			input->set_outputs(output_info);
			//Setting dummy volume to indicate unvisited by the parser
			pair<Node*, int> temp;
			temp.second = 100;
			input->set_outputs(output_info);
		}
		else{
			//Unvisited by parser but visited by other nodes
			if(input->outputs().back().second == 100){
				input->pop_outputs_volume();
				input->set_outputs(output_info);
			}

			//Visited by parser 
			else{
				int volume_left = input->outputs().back().second;
				if(volume_left < output_info.second){
					cout << "Inconsistency at" << output_info.first->name() << endl;
					return;
				}
				else{
					input->pop_outputs_volume();
					input->set_outputs(output_info);
					pair <Node*, int> temp;
					temp.second = volume_left - output_info.second;
					input->set_outputs(temp); 
				}
			}

		}	
}

int IfEven(int n){
	if(n%2==1){
		return 0;
	}
	else 
		return 1;
}