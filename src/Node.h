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
  		Node(string name, Type type, vector<pair<Node*, int> >* inputs, vector<pair<Node*, int> >* outputs);
  		void InputVolumePopulator(int a);
  		string name();
};

#endif

