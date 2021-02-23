#include<fstream>
#include<iostream>
#include <string>
using namespace std;
class CSV {
	ofstream f;
public:
	CSV(string s) {
		f.open(s + "-csv.csv");
	}
	void zatvori() { f.close(); }
	void dodajGranu(string, string);
};