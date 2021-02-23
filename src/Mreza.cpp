#pragma once
#include "Mreza.h"
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <set>
#include "Stajaliste.h"
#include "Linija.h"
#include "Generator.h"
using namespace std;

void Mreza::ucitavanje()
{
	cout << "Unesi '1' za ucitavanje sve a '2' za pojedinacno:";
	int sta;
	cin >> sta;
	if (sta == 1) ucitaj();
	return;
	cout << "Unesi ima linije:";
	string ime;
	cin >> ime;
	ucitajPojedinacno(ime);
}

void Mreza::ucitaj()
{
	ifstream file1("E:\\POOP\\POOP\\POOP\\data\\_lines.txt");
	string s1;
	regex reg1("([^!]*)!([^!]*)!([^!]*)!");

	while (getline(file1, s1)) {
		smatch result1;
		if (regex_match(s1, result1, reg1)) {

			string naziv = result1.str(1);
			string pocetna = result1.str(2);
			string krajnja = result1.str(3);
			linije.push_back(new Linija(naziv));
		}
		else {
			cout << "No match" << endl;
		}
	}
	file1.close();

	for (auto l : linije) {
		string imefajlastaj = "E:\\POOP\\POOP\\POOP\\data\\\\" + l->dohvOznaku() + "_dirA.txt";
		ucitajStajalista(l,imefajlastaj,1);
		imefajlastaj = "E:\\POOP\\POOP\\POOP\\data\\\\" + l->dohvOznaku() + "_dirB.txt";
		ucitajStajalista(l, imefajlastaj, 2);
	}
}

void Mreza::ucitajStajalista(Linija *l, string filename, int smeer)
{
	ifstream file(filename);
	string s;
	regex reg("([^!]*)!([^!]*)!([^!]*)!([^!]*)!(.*)");;
	while (getline(file, s)) {
		smatch result;
		if (regex_match(s, result, reg)) {

			int sifra = atoi(result.str(1).c_str());
			string naziv = result.str(2);
			double x = atof(result.str(3).c_str());
			double y = atof(result.str(4).c_str());
			int zona = atoi(result.str(5).c_str());

			Stajaliste *st = new Stajaliste(sifra, naziv, zona, x, y); //IZGLEDA DA OVDE NE NAPRAVI DOBRO SA OBZIROM DA MI NA ISPIS UVEK VRACA 1
			Stajaliste *novo = vecPostojiSt(st);
			if (novo) {
				l->dodajStajaliste(smeer, novo);
				novo->dodajLiniju(l);
			}
			else {
				l->dodajStajaliste(smeer, st);
				stajalista.push_back(st);
				st->dodajLiniju(l);
			}
		}
		else cout << "NoMatch!" << endl;
	
	}
	file.close();
}

void Mreza::ucitajPojedinacno(string imelinije)
{
	string imefajla = "E:\\jebeni projekat\\poopprojekat\\poopprojekat\\data\\_lines.txt";
	Linija *l;
	ifstream file(imefajla);
	string s;
	regex reg("([^!]*)!([^!]*)!([^!]*)!");

	while (getline(file, s)) {
		smatch result;
		if (regex_match(s, result, reg)) {

			string naziv = result.str(1);
			string pocetna = result.str(2);
			string krajnja = result.str(3);
			Linija *l = new Linija(naziv);
			if (naziv == imelinije) {
				linije.push_back(l);
					string imefajlastaj = "E:\\jebeni projekat\\poopprojekat\\poopprojekat\\data\\" + l->dohvOznaku() + "_dirA.txt";
					ucitajStajalista(l, imefajlastaj, 1);
					imefajlastaj = "E:\\jebeni projekat\\poopprojekat\\poopprojekat\\data\\" + l->dohvOznaku() + "_dirB.txt";
					ucitajStajalista(l, imefajlastaj, 2);
					cout << endl << kolikolinija() << endl;
					cout << endl << kolikostajalista() << endl;
					return;
				

			}
		}
		else {
			cout << "No match" << endl;
		}
	}
	file.close();


}

Stajaliste * Mreza::vecPostojiSt(Stajaliste *st)
{
	for (auto i : stajalista) {
		if (i->dohvatiSifru() == st->dohvatiSifru()) { 
			return i; 
		}
	}
	return nullptr;
}

void Mreza::dodajLinijuRucno() 
{ 
	string oznaka;
	cout << "Unesite oznaku linije:";
	cin >> oznaka;
	linije.push_back(new Linija(oznaka));
}


void Mreza::izbrisiLinijuRucno(string oznaka)
{
	Linija *l;
	for (auto i = linije.begin(); i != linije.end(); i++)
		if ((*i)->dohvOznaku() != oznaka) {
			linije.erase(i);
			l = *i;
		}
	for (auto s : stajalista)
		s->izbrisiLiniju(l);
} 

void Mreza::dodajLinijiStajalisteRucno(string oznaka)
{
	Linija *lin;
	string naziv;
	int sifra, zona, smer;
	double x, y;
	if (!(lin = dohvatiLiniju(oznaka))) {
		cout << "Ta linija ne postoji";
		return;
	}
	cout << "Unesite sifru, naziv, zonu, i koordinate u (x,y) obliku:" << endl;
	cin >> sifra >> naziv >> zona >> x >> y;
	Stajaliste *st = new Stajaliste(sifra, naziv, zona, x, y);
	stajalista.push_back(st);
	cout << "Unesite smer:" << endl;
	cin >> smer;
	lin->dodajStajaliste(smer,st);
	st->dodajLiniju(lin);
	return;
}

void Mreza::izbrisiLinijiStajalisteRucno(string oznaka, int sifs)
{
	for (auto i : linije)
		if (i->dohvOznaku() == oznaka)
		{
			for(auto s : stajalista)
				if (s->dohvatiSifru() == sifs) {
					i->izbrisiStajaliste(1, s);
					i->izbrisiStajaliste(2, s);
				}

		}
}

Linija * Mreza::dohvatiLiniju(string o)
{
	for (auto i : linije)
		if (i->dohvOznaku() == o) return i;
	return nullptr;
}

int Mreza::kolikolinija()
{
	return linije.size();
}

int Mreza::kolikostajalista()
{
	return stajalista.size();
}

void Mreza::izmeneLinija()
{
	int izbor, kraj = 1, sifs;
	string imel;
	while (kraj != 0) {
		cout << "1. Dodaj liniju:" << endl
			<< "2. Izbrisi liniju:" << endl
			<< "3. Promeni oznaku" << endl
			<< "4. Promeni zone kretanja." << endl
			<< "5. Dodaj liniji stajaliste rucno." << endl
			<< "6. Izbrisi stajaliste kroz koje linija prolazi." << endl
			<< "Unesite 0 za prekid ovog dela programa:" << endl
			<< "Unesite:" << endl;
		cin >> izbor;
		switch (izbor) {
		case 1: dodajLinijuRucno();
			break;
		case 2: cout << "Unesite oznaku linije" << endl; cin >> imel; izbrisiLinijuRucno(imel); //POPRAVI OVO SOME
			break;
		case 3: cout << "Unesite oznaku linije" << endl; cin >> imel; promeniOznakuLinije(imel);
			break;
		case 4: promeniZoneLinije(); 
			break;
		case 5: cout << "Unesite oznaku linije:" << endl; cin >> imel; dodajLinijiStajalisteRucno(imel);
			break;
		case 6: cout << "Unesite oznaku linije i sifru stajalista" << endl; cin >> imel >> sifs; izbrisiLinijiStajalisteRucno(imel,sifs); //POPRAVI OVO SOME
			break;
		case 0: return;
		default: cout << "Nedozvoljen izbor:\n" << endl;
		}
	}
}

void Mreza::promeniOznakuLinije(string oznaka)
{
	for (auto i : linije)
		if (i->dohvOznaku() == oznaka)
			i->promeniOznaku(oznaka);
}

void Mreza::promeniZoneLinije()
{
	//POPRAVI OVO SOME
}

vector<Linija*> Mreza::filtrirajZone(int z)
{
	vector<Linija*> novelinije;
	int ok = 1, izbor, br= 0;

	for (auto i : linije) {
		for (auto s : i->dohvatiSmerA())
			if (s->dohvatiZonu() > z) {
				ok = 0;
				continue;
			}
		for (auto s : i->dohvatiSmerB())
			if (s->dohvatiZonu() > z) {
				ok = 0;
				continue;
			}
		if (ok == 1) {
			novelinije.push_back(i);
			br++;
		}
		ok = 1;
		
	}
	cout << br << endl;

	cout << "Da li zelite ispis linija?(1/0" << endl;
	cin >> izbor;
	if (izbor == 1) ispisLinijaVc(novelinije);
	return novelinije;
}

vector<Linija*> Mreza::filtrirajOznakeVeca(int odBr)
{
	vector<Linija*> novelinije;

	for (auto i : linije)
		if (i->brojLinije(i->dohvOznaku()) < odBr) novelinije.push_back(i);
	
	return novelinije;
}

vector<Linija*> Mreza::filtrirajOznakeManja(int doBr)
{
	vector<Linija*> novelinije;

	for (auto i : linije)
		if (i->brojLinije(i->dohvOznaku()) > doBr) novelinije.push_back(i);

	return novelinije;
}

vector<Linija*> Mreza::filtrirajOznakeIzmedju(int odBr, int doBr)
{
	vector<Linija*> novelinije;

	for (auto i : linije)
		if ((i->brojLinije(i->dohvOznaku()) > odBr) && (i->brojLinije(i->dohvOznaku()) < doBr)) novelinije.push_back(i);

	return novelinije;
}

vector<Linija*> Mreza::filtrirarBrStajalistaManje(int br)
{
	vector<Linija*> novelinije;

	for (auto i : linije)
		if ((i->dohvatiBrStajalista(i->dohvatiSmerA()) + (i->dohvatiBrStajalista(i->dohvatiSmerA())) / 2 > br)) novelinije.push_back(i);

	return novelinije;
}

vector<Linija*> Mreza::filtrirarBrStajalistaVece(int br)
{
	vector<Linija*> novelinije;

	for (auto i : linije)
		if ((i->dohvatiBrStajalista(i->dohvatiSmerA()) + (i->dohvatiBrStajalista(i->dohvatiSmerA())) / 2 < br)) novelinije.push_back(i);

	return novelinije;
}

set<Linija*> Mreza::skupLinijaSaZajedStajalist(Linija *l)
{
	set<Linija*> novelinije;
	string imelinije;
	int izbor;
	

	if (l == nullptr) {
		cout << "Ta linija ne postoji!";
		return novelinije;
	}

	for (auto it : l->dohvatiSmerB())
		if(it!=nullptr)
		for (auto lin : it->dohvatiSveLinije())
			if (novelinije.find(lin) == novelinije.end() && lin != l) novelinije.insert(lin);

	for (auto it : l->dohvatiSmerA())
		if (it != nullptr)
			for (auto lin : it->dohvatiSveLinije())
				if (novelinije.find(lin) == novelinije.end() && lin != l) novelinije.insert(lin);


	
	return novelinije;

}

void Mreza::testGraf() {
	Generator g(this);
	g.generisiC();
	g.generisiL();
}

void Mreza::ispisLinija(set<Linija*> ll) {

	//for (auto l : ll)
	//	cout << l->dohvOznaku() << ", ";

	for_each(ll.begin(), ll.end(), [](Linija* l) {
		cout << l->dohvOznaku() << ", ";
	});
}

void Mreza::ispisLinijaVc(vector<Linija*> ll) {

	//for (auto l : ll)
	//	cout << l->dohvOznaku() << ", ";

	for_each(ll.begin(), ll.end(), [](Linija* l) {
		cout << l->dohvOznaku() << ", ";
	});
}
void Mreza::prolaziKrozDva()
{
	Linija *l = nullptr;
	int st1, st2, ok = 0, jeste = 0;
	string imelinije;
	cout << "Unesi oznaku linije:" << endl;
	cin >> imelinije;

	for (auto i : linije)
		if (i->dohvOznaku() == imelinije) {
			l = i;
			break;
		}
	if (l == nullptr) {
		cout << "Ta linija ne postoji!";
		return;
	}

	cout << "Unesi sifru oba stajalista:" << endl;
	cin >> st1 >> st2;

	for (auto s : l->dohvatiSmerA()) {
		if (s->dohvatiSifru() == st1) jeste = 1;
		if (s->dohvatiSifru() == st2) jeste = 2;
	}
	if (jeste == 2) ok = 1;
	jeste = 0;

	for (auto s : l->dohvatiSmerA()) {
		if (s->dohvatiSifru() == st1) jeste = 1;
		if (s->dohvatiSifru() == st2) jeste = 2;
	}
			if(jeste == 2)
				if (ok == 1) ok = 3;
				else ok = 2;

			if (ok == 1) cout << "Prolazi samo u smeru A." << endl;
			if (ok == 2) cout << "Prolazi samo u smeru B." << endl;
			if (ok == 3) cout << "Prolazi u oba smera kroz te dve stanice." << endl;
}

pair<Linija*, int> Mreza::najviseZajednickih()
{
	pair<Linija*, int> par;
	Linija *linijaa, *najviselinija = nullptr;
	string imelinije;
	int br = 0, max = 0;

	cout << " Ponovo unesite tu liniju:" << endl;
	cin >> imelinije;
	linijaa = dohvatiLiniju(imelinije);

	set<Linija*>  telinije = skupLinijaSaZajedStajalist(linijaa);



	for (auto ln : telinije) {
		for (auto st : ln->dohvatiSmerA()) {
			for (auto stp : linijaa->dohvatiSmerA()) {
				if (st->dohvatiSifru() == stp->dohvatiSifru())
					br++;
			}
		}
		if (br > max) {
			max = br;
			br = 0;
			najviselinija = ln;
		}
		else br = 0;
	}

	if(najviselinija) cout << najviselinija->dohvOznaku() << endl;
	else cout << " Nema zajednickih" << endl;
	return par = make_pair(najviselinija, max);

}

Stajaliste* Mreza::najblizeStajaliste()
{
	Stajaliste *st;
	Linija *l = nullptr;
	string oznaka;
	double x, y, raz, min = 9999999999.99;
	int teLinije = 0,yes;

	cout << "Unesi lokaciju:" << endl;
	cin >> x >> y;
	Lokacija lok(x, y);
	cout << "Za odredjeno stajaliste Da/Ne (1/2)?" << endl;
	cin >> yes;
	if (yes == 1) {
		cout << "Unesi oznaku liinje:" << endl;
		cin >> oznaka;

		for (auto i : linije)
			if (i->dohvOznaku() == oznaka) {
				l = i;
				break;
			}
		if (l == nullptr) {
			cout << "Ta linija ne postoji!";
			return nullptr;
		}
	}

	for (auto s : stajalista) {
		if (yes == 1) {
			if(s->dohvatiLiniju(l)) raz = razdaljinaIzmedjuLokacija(s->dohvatiLokaciju(), lok);
			else continue;
		}
		else {
			raz = razdaljinaIzmedjuLokacija(s->dohvatiLokaciju(), lok);
		}

		if (raz < min) {
			min = raz;
			st = s;
		}
	}
	if(st != nullptr)
	cout << endl << st->dohvatiNaziv() << "  " << min << endl;
	return st;

}

double Mreza::razdaljinaIzmedjuLokacija(Lokacija & l1, Lokacija & l2)
{
	double razdaljina;

	return razdaljina = sqrt((l1.getX() - l2.getX())*(l1.getX() - l2.getX()) + (l1.getY() - l2.getY())*(l1.getY() - l2.getY()));
}

void Mreza::brojZajednickihSvihLinija()
{
	//vector<pair<pair<Linija*, Linija*> ,int>> teLinije;
	set<Linija*> imaju;
	int filtr = 0, koliko = 0;
	vector<Linija*> imajuV;
	int brA, brB;

	cout << "Je l zelite da filtrirate na osnovu broja zajednickih stajalisata." << endl;
	cin >> filtr;
	if (filtr == 1) {
		cout << "Unesi granicu." << endl;
		cin >> koliko;
	}

	for (auto lin : linije) {
		imaju = skupLinijaSaZajedStajalist(lin);
		imajuV = prebaci(imaju);
		for (auto i : imajuV) {
			int brA = kolikoZajednickih(lin, i, 1);
			int brB = kolikoZajednickih(lin, i, 2);
			if ((filtr == 1)) {
				if ((koliko < brA) && (koliko < brB)) {
					cout << "Linija " << lin->dohvOznaku() << " i linija " << i->dohvOznaku() << " u smeru A imaju " <<
						brA << " zajedickih stajalista a u smeru B " << brB << " zajednickih stajalista." << endl;
				}
			}
			else {
				if ((brA > 0) && (brB > 0)) {
					cout << "Linija " << lin->dohvOznaku() << " i linija " << i->dohvOznaku() << " u smeru A imaju " <<
						brA << " zajedickih stajalista a u smeru B " << brB << " zajednickih stajalista." << endl;
				}

			}
			
		}
	}



		

}

int Mreza::najmanjePresedanje()
{
	pair<vector<Linija*>, int> par;
	vector<Linija*> lin, linijePresedanja;
	Stajaliste *st1, *st2, *pom1, *pom2;
	bool jeste;
	int br = 0, imest1, max = 9999999,imest2;
	
	cout << "Unesite sifra za oba stajalista: " << endl;
	cin >> imest1 >> imest2;

	st1 = dohvatiSt(imest1);
	st2 = dohvatiSt(imest2);

	for(auto l1 : st1->dohvatiSveLinije())
		for(auto l2 : st2->dohvatiSveLinije())
			if (l1->dohvOznaku() == l2->dohvOznaku()) {
				lin.push_back(l1);
				cout << "Direktna linija " << l1->dohvOznaku() << endl;
				return 0;
			}
	
	
	for (auto lin : st1->dohvatiSveLinije()) {
		int smer = lin->uKomSmeru(st1);
		for (auto lin2 : (lin->sledeceStajaliste(st1,smer))->dohvatiSveLinije())
			if ((lin == lin2) && (st1->dohvatiLiniju(lin2))) {
				br++;
				if (br < max) {
					max = br;
					br = 0;
					//linijePresedanja.push_back(lin2);
				}
				else br = 0;
			}
	}


	cout << max << "Presedanja" << endl;
	return max;



}

vector<Linija*> Mreza::prebaci(set<Linija*> sett)
{
	vector<Linija*> vc;
	for (auto st : sett)
		vc.push_back(st);

	return vc;
}

set<Stajaliste*> Mreza::prebaciUSt(vector<Stajaliste*> vc) {
	set<Stajaliste*> st;
	
	for (auto s : vc)
		if (!st.count(s)) st.insert(s);

	return st;
}

set<Linija*> Mreza::prebaciULn(vector<Linija*> vc) {
	set<Linija*> l;

	for (auto ln : vc)
		if (!l.count(ln)) l.insert(ln);

	return l;
}

void Mreza::filtriranjeOznaka()
{
	int odBr, doBr,izbor;
	vector<Linija*> lin;
	cout << "1. Filtriraj linije sa oznakom manjom od odrenjene:" << endl
		<< "2. Filtriaraj linije sa oznakom vecom od odredjene" << endl
		<< "3. Filtriraj van opsega oznaka" << endl
		<< "Unesi?" << endl;
	cin >> izbor;
	if (izbor == 1) {
		cout << "Unesi oznaku:" << endl;
		cin >> doBr;
		lin = filtrirajOznakeManja(doBr);
	}
	if (izbor == 2) {
		cout << "Unesi oznaku:" << endl;
		cin >> odBr;
		lin = filtrirajOznakeVeca(odBr);
	}
	if (izbor == 3) {
		cout << "Unesi oznake OD-DO" << endl;
		cin >> odBr >> doBr;
		lin = filtrirajOznakeIzmedju(odBr, doBr);
	}

	cout << "Da li zelite ispis linija? (1/0)" << endl;
	cin >> izbor;
	if (izbor == 1) ispisiLinije(lin);
	
	return;

}

void Mreza::ispisiLinije(vector<Linija*> l)
{
	cout << endl;
	for (auto ll : l)
		cout << ll->dohvOznaku() << ", ";
	cout << endl;
}

void Mreza::filtrirajBrStajalista()
{
	int izbor, br;
	vector<Linija*> lin;

	cout << "1. Filtriraj sve sa manjim brojem stajalista:" << endl
		<< "2. Filtriraj sve sa vecim brojem stajalista" << endl
		<< "Unesi:" << endl;

	cin >> izbor;
	cout << "Unesite broj stajalista:" << endl;
	cin >> br;
	if (izbor == 1) lin = filtrirarBrStajalistaManje(br);
	if (izbor == 2) lin = filtrirarBrStajalistaVece(br);

	cout << "Da li zelite ispis linija posle filtriranja?(1/0)" << endl;
	cin >> izbor;
	if (izbor == 1) ispisiLinije(lin);

}

int Mreza::kolikoZajednickih(Linija * l1, Linija * l2, int sm)
{
	int br = 0;

	if (sm == 1) {
		for (auto s1 : l1->dohvatiSmerA())
			for (auto s2 : l2->dohvatiSmerA())
				if (s1->dohvatiSifru() == s2->dohvatiSifru()) br++;

		return br;
	}

	if (sm == 2) {
		for (auto s1 : l1->dohvatiSmerB())
			for (auto s2 : l2->dohvatiSmerB())
				if (s1->dohvatiSifru() == s2->dohvatiSifru()) br++;

		return br;
	}
}

Stajaliste * Mreza::dohvatiSt(int sifra)
{
	for (auto s : stajalista)
		if (s->dohvatiSifru() == sifra) return s;
	return nullptr;
}

Linija * Mreza::dohvatiLn(string oz)
{
	for (auto l : linije)
		if (l->dohvOznaku() == oz) return l;
	return nullptr;
}

int Mreza::zadnjaTacka()
{
	int sif1, sif2;
	Stajaliste *st1, *st2;

	cout << " Unesi sifre oba stajalista. " << endl;
	cin >> sif1 >> sif2;
	st1 = dohvatiSt(sif1);
	st2 = dohvatiSt(sif2);

	vector<Stajaliste*> s1;
	vector<Stajaliste*> s2;
	
	s1.push_back(st1);
	int razdaljina = 1;
	while (s1.size()) {
		while (s1.size()) {
			Stajaliste* tr = s1.back();
				s1.pop_back();
				vector<Stajaliste*> neighbors = svaSusednaStajalista(tr);
				for (auto i : neighbors) {
					s2.push_back(i);
					if (i == st2) return razdaljina;
				}
		}
		razdaljina++;
		s1 = s2;
		s2.clear();
	}
	return -1;


}

vector<Stajaliste*> Mreza::vratiSvaStajalista()
{
	return stajalista;
}


bool Mreza::vecTu(Stajaliste* st, vector<Stajaliste*> vektor)
{
	for (auto s : vektor)
		if (s->dohvatiSifru() == st->dohvatiSifru()) return true;

	return false;
}

vector<Linija*> Mreza::vratiSveLinije() {
	return linije;
}
vector<Stajaliste*> Mreza::svaSusednaStajalista(Stajaliste *st) {
	vector<Stajaliste *> taStajalista;
	int sifra, flag = 0;


	for (auto ln : st->dohvatiSveLinije()) {
		int i = ln->uKomSmeru(st);
		if(!(vecTu(ln->sledeceStajaliste(st, i), taStajalista)))
		taStajalista.push_back(ln->sledeceStajaliste(st, i));
	}

	for (auto a : taStajalista) {
		if (a != nullptr) a;
		//cout << a->dohvatiNaziv() << ", " ;
	}
	//cout << endl << "Ima ih: " << taStajalista.size() << endl;

	return taStajalista;
}



vector<Linija*> Mreza::linijeKojeProlazeKrozSt()
{
	int sifra;
	vector<Linija*> ll;

	cout << "Unesi sifru linije;" << endl;
	cin >> sifra;

	for (auto s : stajalista)
		if (s !=nullptr) 
			if (s->dohvatiSifru() == sifra) ll = s->dohvatiSveLinije();

	for (auto l : ll)
		cout << l->dohvOznaku() << endl;

	return ll;

}

