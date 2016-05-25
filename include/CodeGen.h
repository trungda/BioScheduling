#ifndef CODEGEN_H
#define CODEGEN_H

#include <iostream>                      
#include <string>										
#include <fstream>	

#include "ChipArch.h"
#include "AppGraph.h"
#include "Node.h"

using namespace std;

class CodeGen{
private:
	void PrintBefore(string);
	void PrintAfter(string);
public:
	void ChipInfo(ChipArch);
	void GraphInfo(AppGraph, ChipArch);
	pair< map<string, int>, vector<pair<int, int> > > EdgeInfo(AppGraph);
	void PrintToSource(pair<map<string, int>, vector<pair<int, int> > >, string);
};

#endif