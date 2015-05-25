#include <iostream>                          //cout, cin
#include <string>							 //string class 						
#include <fstream>							 //flie handling
#include <vector>							 //vector class
#include <algorithm>                         //easy-to-use algorithms
#include <utility>                           //pair template
#include <map>                               //using maps
#include "Node.h"
#include "AppGraph.h"

void Printer(AppGraph* ap){                                                     //Debugger
	int i;

	vector<Node*> input = ap->inputs();
	for(i = 0; i < input.size(); i++ ){
		cout << input[i]-> outputs()[0].second << endl;
	}
	cout << endl;

	vector<Node*> internal = ap->internals();
	for(i = 0; i < internal.size(); i++ ){
		cout << internal[i]-> outputs()[0].second << endl;
	}
	cout << endl;

	vector<Node*> output = ap->outputs();
	for(i = 0; i < output.size(); i++ ){
		cout << output[i]-> outputs()[0].second << endl;
	}
	cout << endl;

	return; 
}
pair<Node*, int> MakePair(string output_name, AppGraph app_graph){
	int i;
	string volume_string;
	output_name.pop_back();
	//cout << output_name << '\t';
	for(i=0; i < output_name.size(); i++){
		if(output_name[i]==':'){
			break;
		}
	}
	volume_string = output_name.substr(i+1, 10);
	//cout << volume_string << '\t';

	int volume = stoi(volume_string);
	//cout << volume << '\t';
	output_name = output_name.substr(0, i);
	//cout << output_name << endl ;
	Node* node_address = app_graph.SearchByName(output_name);
	pair<Node*, int> output_pair(node_address, volume);
	return output_pair;
}