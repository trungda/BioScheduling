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
  		string name;
  		Type type;
  		vector<pair<Node*, int> > inputs;
  		vector<pair<Node*, int> > outputs;
	public:
  		Node();
  		Node(string Name, Type optype);
  		Node(string Name, Type optype, vector<pair<Node*, int> >* iputs, vector<pair<Node*, int> >* oputs);
  		void InputVolumePopulator(int a);
  		string NameAccess();
};

#endif

