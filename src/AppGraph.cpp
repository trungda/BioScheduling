#include <iostream>                      
#include <string>										
#include <fstream>							
#include <vector>						
#include <algorithm>                       
#include <utility>                         
#include <map>   
#include <unordered_set>  
#include <iomanip>                    

#include "../include/AppGraph.h"
#include "../include/Node.h"

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
	cout << "ID\t|" << "\t  INPUTS\t\t\n";	 
	for(i=0; i<outputs_.size(); i++){
		cout << outputs_.at(i)->name() << "\t|\t";
		for(j=0; j<outputs_.at(i)->inputs().size(); j++){
			cout << "|" << setw(4) << outputs_.at(i)->inputs().at(j).first->name()<< ":"
			<<  setw(3) << outputs_.at(i)->inputs().at(j).second << "|";
		}
		cout << endl;
	}
	cout << endl;
}

void AppGraph::PrintInputs(){
	int i;
	int j;
	cout << "Input type\n" << endl;
	cout << "ID\t|" << "\t  OUTPUTS\t\t\n";	 
	for(i=0; i<inputs_.size(); i++){
		cout << inputs_.at(i)->name() << "\t|\t";
		//Last element contains only volume_left information
		for(j=0; j<inputs_.at(i)->outputs().size()-1; j++){
			cout << "|" << setw(4) << inputs_.at(i)->outputs().at(j).first->name()<< ":"
			<<  setw(3)<< inputs_.at(i)->outputs().at(j).second << "|";
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
			cout << "|" << setw(4) << internals_.at(i)->inputs().at(j).first->name()<< ":"
			<<  setw(3) << internals_.at(i)->inputs().at(j).second << "|";
		}
		cout << "\t|\t";
		for(j=0; j<internals_.at(i)->outputs().size(); j++){
			cout << "|" << setw(4) << internals_.at(i)->outputs().at(j).first->name()<< ":"
			<<  setw(3) << internals_.at(i)->outputs().at(j).second << "|";
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

AppGraph::AppGraph(string filename, Node* createnode){

	map<string, Type> conversion;                    
	conversion["INPUT"] = Input;
	conversion["OUTPUT"] = Output;
	conversion["MIX"] = Mix;

	unordered_map <string, Node*> SearchMap;

	ifstream inputfile_1(filename);

    string name, type_string;
    string garbage;
    Type type;
    char ch;
    int i;
    //Node createnode[1000]; 
    unordered_map <string, Node*>::iterator got;                                               

    //First-Pass
    if(inputfile_1.is_open()){                             
	    for(i=0; !inputfile_1.eof(); i++){

	    	//Reads the Name
			inputfile_1 >> name;

			//Case:end of inputs
			if(name == "#end")
				break;

			ch = name.at(0);

			//Ignores comments i.e. lines beginning with '#'
			//Ignores Input-Output information i.e strings beginning with '('
			if(ch!='#' && ch!='('){

				//Reads the type
				inputfile_1 >> type_string;

				if(type_string.at(0)=='I'){

					//Keeps only "Input"                           
					type_string.resize(5);
				}
				type = conversion[type_string];
				Node temp(name, type);
				createnode[i]= temp;

				got = SearchMap.find(name);
				if(got == SearchMap.end()){

					//Hash_Map between the node name and address
					SearchMap.emplace(make_pair(name, createnode+i));

					//Add the node to the graph
					this->AddNode(createnode+i);
				}

				else{
					cout << "ID collision" << endl;
					cout << "Multiple occurences of " << name << endl;
					abort();
				}
			}
			else{
				//Skips the line
				getline(inputfile_1, garbage);
			}
		}
    }

    //Checks whether the graph has inputs and outputs
    this->InputOutputCheck();

    //Second-Pass
	ifstream inputfile_2(filename);

	string input_name, output_name, volume_string;           
	int inputs_counter=0, internals_counter=0;
	int volume;
	Node* node_address;
	Node* curr_address;

	if(inputfile_2.is_open()){                                    
		while(!inputfile_2.eof()){

			//Reads the name
			inputfile_2 >> name;

			ch = name.at(0);

			//Ignores comments i.e. lines beginning with '#'
			if(ch!='#'){

				//Reads the type
				inputfile_2 >> type_string;

				if(type_string.at(0)== 'I'){
					curr_address = this->inputs().at(inputs_counter);

					//Keeps only the volume-x from INPUT:x
					type_string.erase(0, 6);

					volume = stoi(type_string);

					//Places the volume information in the node
					//Additional functionality explained in the function definition
					curr_address->set_outputs_volume(volume);

					inputs_counter++;
				}
				else if(type_string.at(0)== 'M'){
					Node* curr_address = this->internals()[internals_counter];

					//First Input
					inputfile_2 >> input_name;
					input_name.erase(0, 1);
					input_name.pop_back();

					//Searches for node with the name "input_name"
					//Returns a pointer to that node
					node_address = this->SearchByName(input_name, SearchMap);

					//Places the pointer to the input node in the current node
					//Additional functionaltiy explained in the function definition
					curr_address->SetInputsPointer(node_address);

					//Second Input
					inputfile_2 >> input_name;
					input_name.pop_back();
					node_address = this->SearchByName(input_name, SearchMap);
					curr_address->SetInputsPointer(node_address);

					//First Output
					inputfile_2 >> output_name;
					output_name.erase(0, 1);
					pair<Node*, int> output_info = this->MakePair(output_name, SearchMap);
					this->AddEdge(curr_address, output_info.first, output_info.second);

					//Remaining Outputs
					while(output_name.back()!=')'){
						inputfile_2 >> output_name;

						//MakePair(013:23, this-> would return pair<013*, 23>
						pair<Node*, int> output_info = this->MakePair(output_name, SearchMap);

						//Adds edge between the two nodes with the given weight
						//Additional functionaltiy explained in the function definition
						this->AddEdge(curr_address, output_info.first, output_info.second);
					}

					curr_address->ConsistencyCheck();
					internals_counter++;
 				}
			}
			else{
				//Skip the line
				getline(inputfile_2, garbage);
			}
		}
    }

    //To check if all Input volume is consumed
    this->InputVolumeConsumeCheck();

    //To check if the inflow and outflow is same in internal nodes
    this->InternalsVolumeConsistencyCheck();
}
