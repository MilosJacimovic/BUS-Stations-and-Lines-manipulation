#include "GML.h"
#include <string>

void GML::dodajCvor(string id) 
{
	f << "node\n[\nid " << id << "\n]\n";
}

void GML::dodajGranu(string a, string b)
{
	f << "edge\n[\nsource " << a << "\ntarget " << b << "\n]\n";
}
