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


//Used in second pass-only
//Used only for internal Nodes
void SetInputsPointer(Node* curr, Node* parent){

	//dummy_volume: A pair in the input vector of the "curr" node has this
	//              volume only if it was set by this "curr" node itself
	const int dummy_volume = 100;

	//Parser visits the "curr" node before visiting either of its parents
	//Case: "curr" node setting its first input
	//OR
	//Case: "curr" node setting its second input	
	if(curr->inputs().empty() || (curr->inputs().size() == 1 && curr->inputs().at(0).second == dummy_volume) ){  
		pair<Node*, int> temp(parent, dummy_volume);
		curr->set_inputs(temp);
	}

	//Parser visits the "curr" node after both parents have been visited
	//Case: first input != parent
	//AND
	//Case: second input!= parent
	else if(curr->inputs().size()==2 && curr->inputs()[0].first!= parent && curr->inputs()[1].first!= parent){
			cout << "Inconsistency at " << curr->name()  << endl;
			abort();
	}

	//Parser visits the "curr" node after one of its parents have been visited
	else if(curr->inputs().size()==1 && curr->inputs().at(0).second != dummy_volume){

		//Case: first input (the only input) != parent
		if(curr->inputs().at(0).first != parent){
			pair<Node*, int> temp(parent, dummy_volume);
			curr->set_inputs(temp);	
		}
	}
	return;
}

//Used only for Input nodes
void SetInputs(Node* input, pair<Node*, int> output_info){

	//dummy_volume to indicate that it has not been visited by parser but by other nodes	
	const int dummy_volume = 100;

	if(input->outputs().empty()){
			input->set_outputs(output_info);
			//Setting dummy_volume to indicate unvisited by the parser
			pair<Node*, int> temp;
			temp.second = dummy_volume;
			input->set_outputs(temp);
	}
	else{
		//Unvisited by parser but visited by other nodes
		if(input->outputs().back().second == dummy_volume){
			input->pop_outputs();
			input->set_outputs(output_info);
			pair<Node*, int> temp;
			temp.second = dummy_volume;
			input->set_outputs(temp);
		}

		//Visited by parser 
		else{
			int volume_left = input->outputs().back().second;

			//Case: Available Volume < Required
			if(volume_left < output_info.second){
				cout << "Volume Inconsistency at " << input->name() << "\nOutflow > Volume Specified" << endl;
				abort();
			}
			else{
				input->pop_outputs();
				input->set_outputs(output_info);
				pair <Node*, int> temp;
				temp.second = volume_left - output_info.second;
				input->set_outputs(temp); 
			}
		}
	}
	return;	
}

int IfEven(int n){
	if(n%2==1){
		return 0;
	}
	else 
		return 1;
}

//Checks for even outflow
//Sets the outputs_ for the parents of this node if they are of "Input" type
void ConsistencyCheck(Node* start){

	int i;
	
	//volume_sum: total volume flowing out of this node
	int volume_sum = 0;
	
	for(i=0; i<start->outputs().size(); i++)
		volume_sum += start->outputs().at(i).second;

	//To ensure even outflow
	if(!IfEven(volume_sum)){
		cout << "Volume outflow not even at " << start->name() << "\nIt is: " << volume_sum << endl;
		abort();
	}
	
	pair<Node*, int> output_info (start, volume_sum/2);

	if(start->inputs().at(0).first->type() == Input){
		start->set_inputs_volume (0, volume_sum/2);
		SetInputs(start->inputs().at(0).first, output_info);
	}

	else if(start->inputs().at(0).second != volume_sum/2 && start->inputs().at(0).second != 100 ){
		cout << "Inconsistency at "  << start->inputs().at(0).first->name() <<"\nOutflow to "
		<< start->name() << ' ' << " is not the same as required" << endl;
		abort();
	}

	if(start->inputs().at(1).first->type() == Input){
		start->set_inputs_volume (1, volume_sum/2);
		SetInputs(start->inputs().at(1).first, output_info);
	}

	else if(start->inputs().at(1).second != volume_sum/2 && start->inputs().at(1).second != 100){
		cout << "Inconsistency at " << start->inputs().at(1).first->name() <<"\nOutflow to "
		<< start->name() << ' ' << " is not the same as required" << endl;
		abort();
	}

	return;
}