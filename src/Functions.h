#ifndef FUNCTIONS_H
#define FUCTIONS_H

#include <iostream>                      
#include <string>										
#include <fstream>							
#include <vector>						
#include <algorithm>                       
#include <utility>                         
#include <map> 
#include <unordered_set> 


#include "AppGraph.h"
#include "Node.h"

using namespace std;

pair<Node*, int> MakePair(string, AppGraph, unordered_map <string, Node*>);
void SetInputsPointer(Node* curr, Node* parent);
int IfEven(int);
void SetInputs(Node*, pair<Node*, int>);
void ConsistencyCheck(Node* node);

#endif