#include "Node.h"
#include <iostream>                          //cout, cin
#include <string>							 //string class 						
#include <fstream>							 //flie handling
#include <vector>							 //vector class
#include <algorithm>                         //easy-to-use algorithms
#include <utility>                           //pair template
#include <map>                               //using maps
using namespace std;

Node::Node(){
	name = "default";
  	type = Input;
}

Node::Node (string Name, Type optype){                                                                      //Constructor for the 
    name = Name;                                                                                       //first pass
    type = optype;
}

