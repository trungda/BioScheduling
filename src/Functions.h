#ifndef FUNCTIONS_H
#define FUCTIONS_H

#include <iostream>                      
#include <string>										
#include <fstream>							
#include <vector>						
#include <algorithm>                       
#include <utility>                         
#include <map>                           

#include "AppGraph.h"
#include "Node.h"

pair<Node*, int> MakePair(string, AppGraph);
void SetInputsPointer(Node* curr, Node* parent);
int IfEven(int);
void SetInputs(Node*, pair<Node*, int>);
void ConsistencyCheck(Node* node);

#endif