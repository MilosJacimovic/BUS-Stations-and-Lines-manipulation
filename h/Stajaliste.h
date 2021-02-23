#include <string>
#include <iostream>
#include <set>
#include <vector>
#include "Lokacija.h"
class Linija;

using namespace std;

class Stajaliste {

private:
	int sifra, zona;
	string naziv;
	Lokacija lokacija;
	vector<Linija*> linije;

public:
	Stajaliste(int sifra, string naziv, int zona, double x, double y):lokacija(x, y) {
		this->sifra = sifra;
		this->naziv = naziv;
		this->zona = zona;
	}

	void dodajLiniju(Linija *l);
	void izbrisiLiniju(Linija *l);

	bool dohvatiLiniju(Linija *l);

	vector<Linija*> dohvatiSveLinije();

	int dohvatiSifru() const;
	void promeniSifru(int sif);

	int dohvatiZonu() const;
	void promeniZonu(int zon);
	string dohvatiNaziv() const;
	Lokacija dohvatiLokaciju() const;

	int dohvatiSifru();

	friend ostream& operator<<(ostream& it, const Stajaliste &s);

	bool operator==(Stajaliste s);

};