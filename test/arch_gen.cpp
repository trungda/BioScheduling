#include <iostream>
#include <fstream>

using namespace std;

int main(){
	int n_m, n_r, t;
	cin >> n_m >> n_r >> t;
	ofstream myfile;
	myfile.open("chip_arch.txt", ios::trunc);
	myfile << "#Module-Type\t\tNumber\t\tTime" << endl;
	myfile << "Mixer\t\t\t" << n_m << "\t\t" << t << endl;	
	myfile << "Reservoir\t\t" << n_r << "\t\t" << 0 << endl;
	myfile << "#end" << endl;
	myfile.close();
}