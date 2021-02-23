#include <string>
#include <vector>
#include <iostream>
#include <regex>
class Stajaliste;
using namespace std;


class Linija {
private:
	string oznaka;
	vector<Stajaliste*> smerA, smerB;
	int zone[4];

public:
	Linija(string oznaka);

	void dodajStajaliste(int smer, Stajaliste *s);
	void izbrisiStajaliste(int smer, Stajaliste *s);

	int* dohvZone();

	int uKomSmeru(Stajaliste *s);
	
	Stajaliste* sledeceStajaliste(Stajaliste *s, int smeer);
	
	void dodajZonu(int z);
	string dohvOznaku() const;
	vector<Stajaliste*> dohvatiSmerA() const;
	vector<Stajaliste*> dohvatiSmerB() const;
	void promeniOznaku(string oz);
	int brojLinije(string s) {
		regex reg("[^0-9]*([0-9]*).*");
		smatch result;

		if (regex_match(s, result, reg)) {
			return atoi(result.str(1).c_str());
		}
		return -1;
	}
	void promeniZone();
	int dohvatiBrStajalista(vector<Stajaliste*> st);
	friend ostream& operator<<(ostream &it, const Linija&l);


	bool prolaziKroz(Stajaliste s, int kojismer);

	bool operator==(Linija l);

};