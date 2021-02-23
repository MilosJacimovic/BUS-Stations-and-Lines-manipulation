#include "Linija.h"
#include <iostream>
#include <vector>
#include <string>
#include "Stajaliste.h"
using namespace std;

Linija::Linija(string oznaka)
{
	this->oznaka = oznaka;
	for (int &a : zone) a = 0;
}

void Linija::dodajStajaliste(int smer, Stajaliste * s)
{
	if (smer == 1) {
		smerA.push_back(s);
		dodajZonu(s->dohvatiZonu());
	}
	else {
		smerB.push_back(s);
		dodajZonu(s->dohvatiZonu());
	}

	return;
}

void Linija::izbrisiStajaliste(int smer, Stajaliste * s)
{
	if (smer == 1)
		for (auto st = smerA.begin(); st != smerA.end(); st++)
			if ((*st)->dohvatiSifru() == s->dohvatiSifru()) smerA.erase(st);
	if(smer == 2)
		for (auto st = smerB.begin(); st != smerB.end(); st++)
			if ((*st)->dohvatiSifru() == s->dohvatiSifru()) smerB.erase(st);
}


int * Linija::dohvZone()
{
	return zone;
}

int Linija::uKomSmeru(Stajaliste * s) {
	for (auto sm : smerA)
		if (sm->dohvatiSifru() == s->dohvatiSifru()) return 1;

	for (auto sm : smerB)
		if (sm->dohvatiSifru() == s->dohvatiSifru()) return 2;

}

Stajaliste * Linija::sledeceStajaliste(Stajaliste * s, int smeer)	 {
	
	int flag = 0;

	if (smeer == 1)
		for (auto st : smerA) {
			if (st->dohvatiSifru() == s->dohvatiSifru()) {
				flag = 1;
				continue;
			}
			if (flag == 1) {
				return st;
			}

		}
	if (smeer == 2)
		for (auto st : smerB) {
			if (st->dohvatiSifru() == s->dohvatiSifru()) {
				flag = 1;
				continue;
			}
			if (flag == 1) return st;

		}
}



void Linija::dodajZonu(int z)
{
	for (int i : zone)
		if (i == z) return;
	zone[z - 1] = z;
	return;
}

string Linija::dohvOznaku() const
{
	return oznaka;
}

vector<Stajaliste*> Linija::dohvatiSmerA() const
{
	return smerA;
}

vector<Stajaliste*> Linija::dohvatiSmerB() const
{
	return smerB;
}

void Linija::promeniOznaku(string oz)
{
	this->oznaka = oznaka;
}




int Linija::dohvatiBrStajalista(vector<Stajaliste*> st)
{
	return st.size();
}

bool Linija::operator==(Linija l)
{
	if (l.oznaka == this->oznaka) return true;
	return false;
}

