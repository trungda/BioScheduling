#ifndef NODE_H
#define NODE_H
#include <iostream>                          
#include <string>							 
#include <fstream>							
#include <vector>							 
#include <algorithm>                         
#include <utility>                           
#include <map>                               
using namespace std;

enum Type {Input, Output, Mix};

class Node{
	private:
  		string name_;
  		Type type_;
  		vector<pair<Node*, int> > inputs_;
  		vector<pair<Node*, int> > outputs_;
	public:
  		Node();
  		Node(string name, Type type);
  		void InputVolumePopulator(int a);
      void InputPointerPopulator(Node *);
  		string name();
      Type type();
      vector<pair<Node*, int> > outputs();
      vector<pair<Node*, int> > inputs();
      void set_outputs(pair<Node*, int> output_info);
      void set_inputs(pair<Node*, int> inuput_info);
      int SearchByName(string);
};

#endif

