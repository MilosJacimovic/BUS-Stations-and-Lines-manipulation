#include "Generator.h"
#include"GML.h"
#include"CSV.h"
#include "Mreza.h"
#include "Linija.h"
#include "Stajaliste.h"
#include <vector>
void Generator::generisiL()
{
	GML* gml = new GML("L");
	CSV* csv = new CSV("L");
	//dodavanje
	set<Stajaliste*> prosle;
	vector<Stajaliste*> pom;
	vector<Stajaliste*> staja = mm->vratiSvaStajalista();
	set<Stajaliste*> stajal = mm->prebaciUSt(staja);
	for (auto st : stajal) {
		 pom = mm->svaSusednaStajalista(st);
		set<Stajaliste*> zajLin = mm->prebaciUSt(pom);
		 for (auto ln : zajLin) {
			
			prosle.insert(st);
			prosle.insert(ln);
			csv->dodajGranu(to_string(st->dohvatiSifru()), to_string(ln->dohvatiSifru()));
			gml->dodajGranu(to_string(st->dohvatiSifru()), to_string(ln->dohvatiSifru()));
			if (prosle.find(st) == prosle.end()) gml->dodajCvor(to_string(st->dohvatiSifru()));
			if (prosle.find(ln) == prosle.end()) gml->dodajCvor(to_string(ln->dohvatiSifru()));
		}
	}
	gml->zatvori();
	csv->zatvori();
}

void Generator::generisiC()
{
	GML* gml = new GML("C");
	CSV* csv = new CSV("C");
	set<Linija*> prosle;
	//dodavanje
	
	vector<Linija*> linij = mm->vratiSveLinije();
	set<Linija*> linije = mm->prebaciULn(linij);
	for (auto l : linije) {
		set<Linija*> zajLin = mm->skupLinijaSaZajedStajalist(l);
		for (auto ln : zajLin) {
			prosle.insert(l);
			prosle.insert(ln);
			csv->dodajGranu(l->dohvOznaku(), ln->dohvOznaku());
			gml->dodajGranu(l->dohvOznaku(), ln->dohvOznaku());
			if (prosle.find(l) == prosle.end()) gml->dodajCvor(l->dohvOznaku());
			if (prosle.find(ln) == prosle.end()) gml->dodajCvor(ln->dohvOznaku());
		}
	}
	gml->zatvori();
	csv->zatvori();


}
