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
		cout << input[i]-> name() << endl;
	}
	return; 
}
