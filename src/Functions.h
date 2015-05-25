#ifndef FUNCTIONS_H
#define FUCTIONS_H
#include <iostream>                          //cout, cin
#include <string>							 //string class 						
#include <fstream>							 //flie handling
#include <vector>							 //vector class
#include <algorithm>                         //easy-to-use algorithms
#include <utility>                           //pair template
#include <map>                               //using maps
#include "Node.h"
#include "AppGraph.h"

void Printer(AppGraph* ap);
pair<Node*, int> MakePair(string, AppGraph);
#endif