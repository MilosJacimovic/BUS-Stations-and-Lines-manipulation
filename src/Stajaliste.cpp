#include "Stajaliste.h"
#include "Linija.h"
#include <iostream>
#include <vector>
#include <set>
#include <string>
using namespace std;
class Linije;

void Stajaliste::dodajLiniju(Linija * l)
{
	linije.push_back(l);
}

void Stajaliste::izbrisiLiniju(Linija * l)
{
	for (auto i = linije.begin(); i != linije.end(); i++)
		if ((*i)->dohvOznaku() == l->dohvOznaku()) linije.erase(i);
}

bool Stajaliste::dohvatiLiniju(Linija * l)
{
	for (auto lin : linije)
		if (lin->dohvOznaku() == l->dohvOznaku()) return true;
	return false;
}

vector<Linija*> Stajaliste::dohvatiSveLinije()
{
	return linije;
}


int Stajaliste::dohvatiSifru() const
{
	return this->sifra;
}

void Stajaliste::promeniSifru(int sif)
{
	this->sifra = sif;
}

int Stajaliste::dohvatiZonu() const
{
	return this->zona;
}

void Stajaliste::promeniZonu(int zon)
{
	this->zona = zon;
}

string Stajaliste::dohvatiNaziv() const
{
	return this->naziv;
}

Lokacija Stajaliste::dohvatiLokaciju() const
{
	return lokacija;
}

int Stajaliste::dohvatiSifru()
{
	return this->sifra;
}

bool Stajaliste::operator==(Stajaliste s)
{
	if (s.sifra == this->sifra) return true;
	return false;
}

ostream & operator<<(ostream& it, const Stajaliste & s)
{
	it << s.dohvatiSifru() << s.dohvatiNaziv() << s.dohvatiLokaciju();
	return it;
}
