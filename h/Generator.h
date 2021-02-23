#pragma once
#include <iostream>
class Mreza;
class Generator {
	Mreza* mm;
public:
	Generator(Mreza* m) :mm(m) {}
	void generisiL();
	void generisiC();
};