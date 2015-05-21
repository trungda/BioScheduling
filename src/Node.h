#ifndef NODE_H
#define NODE_H
#include <iostream>                          //cout, cin
#include <string>							 //string class 						
#include <fstream>							 //flie handling
#include <vector>							 //vector class
#include <algorithm>                         //easy-to-use algorithms
#include <utility>                           //pair template
#include <map>                               //using maps
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
};

#endif

