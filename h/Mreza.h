#include <iostream>
#include <string>
#include<set>
#include <vector>
#include <map>
class Linija;
class Stajaliste;
class Lokacija;
using namespace std;


class Mreza {

private:

	vector<Linija*> linije;
	vector<Stajaliste*> stajalista;

public:

	void ucitavanje();
	void ucitaj();
	void ucitajStajalista(Linija *l, string filename, int smeer);
	void ucitajPojedinacno(string imefajla);
	Stajaliste* vecPostojiSt(Stajaliste *st);

	void dodajLinijuRucno();
	void izbrisiLinijuRucno(string oznaka);
	void dodajLinijiStajalisteRucno(string oznaka);
	void izbrisiLinijiStajalisteRucno(string oznaka,int sifs);
	Linija* dohvatiLiniju(string o);
	int kolikolinija();
	int kolikostajalista();
	void izmeneLinija();
	void promeniOznakuLinije(string oznaka);
	void promeniZoneLinije();


	vector<Linija*> filtrirajZone(int z);

	vector<Linija*> filtrirajOznakeVeca(int odBr);
	vector<Linija*> filtrirajOznakeManja(int doBr);
	vector<Linija*> filtrirajOznakeIzmedju(int odBr, int doBr);

	vector<Linija*> filtrirarBrStajalistaManje(int br);

	vector<Linija*> filtrirarBrStajalistaVece(int br);

	set<Linija*> skupLinijaSaZajedStajalist(Linija *l);

	void prolaziKrozDva();

	pair<Linija*, int> najviseZajednickih();
	
	Stajaliste* najblizeStajaliste();
	double razdaljinaIzmedjuLokacija(Lokacija &l1, Lokacija &l2);

	void brojZajednickihSvihLinija();

	int najmanjePresedanje();

	vector<Linija*> prebaci(set<Linija*> sett);

	void filtriranjeOznaka();

	void ispisiLinije(vector<Linija*> l);

	void filtrirajBrStajalista();

	int kolikoZajednickih(Linija *l1, Linija *l2, int sm);
	Stajaliste* dohvatiSt(int sifra);
	Linija* dohvatiLn(string oz);

	void testGraf();
	int zadnjaTacka();
	void ispisLinijaVc(vector<Linija*> ll);
	void ispisLinija(set<Linija*> ll);

	set<Linija*> prebaciULn(vector<Linija*> vc);

	set<Stajaliste*> prebaciUSt(vector<Stajaliste*> vc);

	vector<Stajaliste*> vratiSvaStajalista();

	vector<Linija*> vratiSveLinije();

	bool vecTu(Stajaliste* st, vector<Stajaliste*> vektor);
	vector<Stajaliste *> svaSusednaStajalista(Stajaliste *st);

	Stajaliste najblizeGeografski(double x, double y, Linija l);
	pair<Linija, Linija> brZajedStajZaParove(Linija l, int granica);

	vector<Linija*> linijeKojeProlazeKrozSt();

	vector<Stajaliste> maksJednaStanica();

};