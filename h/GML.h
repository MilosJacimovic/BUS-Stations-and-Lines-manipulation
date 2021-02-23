#include<fstream>
#include<iostream>
#include <string>
using namespace std;


class GML {
	ofstream f;
public:
	GML(string s) {
		f.open(s + "-gml.gml");
		f << "graph\n[\n";
	}
	void zatvori() { f << "]"; f.close(); }
	void dodajCvor(string);
	void dodajGranu(string,string);
	
};