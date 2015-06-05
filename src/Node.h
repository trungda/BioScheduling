#ifndef NODE_H
#define NODE_H

#include <iostream>                          
#include <string>							 
#include <fstream>							
#include <vector>							 
#include <algorithm>                         
#include <utility>                           
#include <map> 
#include <unordered_set> 

using namespace std;

enum Type {Input, Output, Mix};

class Node{
	private:
  		string name_;
  		Type type_;
  		vector<pair<Node*, int> > inputs_;
  		vector<pair<Node*, int> > outputs_;
      void set_inputs_pointer(Node *); 
      void pop_outputs();
      void SetInputs(pair<Node*, int> output_info);

	public:
  		Node();
  		Node(string name, Type type);

      string name();
      Type type();
      vector<pair<Node*, int> > inputs();
      vector<pair<Node*, int> > outputs();
      void set_inputs(pair<Node*, int> inuput_info);
      void set_outputs(pair<Node*, int> output_info);
  		void set_outputs_volume(int a);  
      void set_inputs_volume(int index, int volume); 
      void ConsistencyCheck(); 
      void SetInputsPointer(Node* parent); 
};

#endif

