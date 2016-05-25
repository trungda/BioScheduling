#include <iostream>                      
#include <string>										
#include <fstream>							
#include <vector>						
#include <algorithm>                       
#include <utility>                         
#include <map> 
#include <unordered_map> 
#include <iomanip>

#include "../../include/ChipArch.h"

using namespace std;


ChipArch::ChipArch(string filename){

	map<string, Module> conversion;                    
	conversion["Mixer"] = Mixer;
	conversion["Heater"] = Heater;
	conversion["Detector"] = Detector;
	conversion["Reservoir"] = Reservoir;

	string module_string, garbage;
	Module module;
	int number, op_time;
	char ch;	

	ifstream inputfile(filename);

	if(inputfile.is_open()){
		while(!inputfile.eof()){
			inputfile >> module_string;

			if(module_string == "#end")
				break;

			ch = module_string.at(0);

			if(ch != '#'){
				module = conversion[module_string];
				inputfile >> number;
				inputfile >> op_time;

				this->Set(module, number, op_time);
			}
			else{
				getline(inputfile, garbage);
			}
		}
	}
}

void ChipArch::Set(Module module, int number, int op_time){
	pair <int, int> temp (number, op_time);
	switch(module){
		case Mixer: mixers_ = temp; break;
		case Heater: heaters_ = temp; break;
		case Detector: detectors_ = temp; break;
		case Reservoir: reservoirs_ = temp; break;
	}
	return;
}

void ChipArch::PrintMixers(){

	cout << setw(10) << "Mixers" << '\t' << mixers_.first << '\t' << mixers_.second << 's' << endl;
}

void ChipArch::PrintHeaters(){
	cout << setw(10) << "Heaters" << '\t' << heaters_.first << '\t' << heaters_.second << 's' << endl;
}

void ChipArch::PrintDetectors(){
	cout << setw(10) << "Detectors" << '\t' << detectors_.first << '\t' << detectors_.second << 's' << endl;
}

void ChipArch::PrintReservoirs(){
	cout << setw(10) << "Reservoirs" << '\t' << reservoirs_.first << '\t' << reservoirs_.second << 's' << endl;
}

pair<int, int> ChipArch::mixers(){
	pair<int, int> info;
	int n_m = mixers_.first;
	int T = mixers_.second;
	info = make_pair (n_m, T);
	return info;
}

int ChipArch::reservoirs(){
	int n_r;
	n_r = reservoirs_.first;
	return n_r;
}

