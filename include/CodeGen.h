#ifndef CODEGEN_H
#define CODEGEN_H

#include <iostream>                      
#include <string>										
#include <fstream>	

#include "ChipArch.h"
#include "AppGraph.h"
#include "Node.h"

using namespace std;

map<string, int> start_time;
vector<pair<int, int> > edges;

class CodeGen{
private:
	void PrintBefore(string);
	void PrintAfter(string);
	void ChipInfo(ChipArch);
	void GraphInfo(AppGraph, ChipArch);
	void EdgeInfo(AppGraph, string &);
	void PrintToSource(string, string &);
public:
	void Generate(ChipArch, AppGraph, string);
};

#endif