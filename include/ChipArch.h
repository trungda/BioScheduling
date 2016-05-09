#ifndef CHIPARCH_H
#define CHIPARCH_H

#include <iostream>                      
#include <string>										
#include <fstream>							
#include <vector>						
#include <algorithm>                       
#include <utility>                         
#include <map> 
#include <unordered_map>                          

#include "Node.h" 
                           
using namespace std;

enum Module {Mixer, Heater, Detector, Reservoir};

class ChipArch{
	private:
		pair <int, int> mixers_;
		pair <int, int> heaters_;
		pair <int, int> detectors_;
		pair <int, int> reservoirs_;
		void Set(Module module, int number, int time);
	public:
		ChipArch (string filename);
		void PrintMixers();
		void PrintHeaters();
		void PrintDetectors();
		void PrintReservoirs();
};
#endif