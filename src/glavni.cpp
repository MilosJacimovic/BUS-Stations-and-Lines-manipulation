#include <iostream>
#include <string>
#include "Mreza.h"
#include <cstdlib>
#include <fstream>
#include <regex>
#include <iomanip>
using namespace std;

void main() {
	int kraj = 1, izbor, zone;
	string ozz;
	Stajaliste *s;
	Linija *l;
	Mreza m;

	while (kraj != 0) {
		cout << "1. Pojedinacno ucitaj liniju i njena stajista:" << endl
			<< "2. Grupno ucitavanje svega:" << endl
			<< "3. Izmeni podatke o liniji:" << endl
			<< "4. Filtriraj spisak linija na osnovu zona kroz koje linija prolazi:" << endl
			<< "5. Filtriraj spisak linija na osnovu oznake:" << endl
			<< "6. Filtriraj spisak linija na osnovu broja stajalista kroz koja prolaze:" << endl
			<< "7. Skup linija sa kojima data linija ima zajednicka stajalista:" << endl
			<< "8. Da li linija prolazi kroz zadata dva stajalista u oba smera:" << endl
			<< "9. Linija sa kojom zadata linija ima najvise zajednickih stajalista:" << endl
			<< "10. Najblize stajaliste u odnosu na zadatu geografsku lokaciju:" << endl
			<< "11 Odredjivanje broja zajednickih stajalista za sve parove linija koje imaju zajednicko stajaliste:" << endl
			<< "12. Odredjivanje svih linija koje prolaze kroz dato stajaliste:" << endl
			<< "13. Odredjivanje svih linija do kojih je moguce stici iz zadatog stajalista:" << endl
			<< "14. Odredjivanje najmanjeg potrebnog broja presedanja na putu izmedju dva stajalista:" << endl
			<< "15. Odredjivanje najkraceg puta izmedju dva stajalista(najmanji broj stajalista izmedju):" << endl
			<< "Unesite zeljeni redni broj." << endl;
		cin >> izbor;
		switch (izbor) {
		case 1: m.ucitavanje();
			break;
		case 2: m.ucitavanje();
			break;
		case 3: m.izmeneLinija();
			break;
		case 4: cout << "Unesi do koje zone: "; cin >> zone; m.filtrirajZone(zone);
			break; 
		case 5: m.filtriranjeOznaka();
			break;	
		case 6: m.filtrirajBrStajalista();
			break;
		case 7: cout << "Unesi oznaku linije" << endl; cin >> ozz; l = m.dohvatiLn(ozz); m.skupLinijaSaZajedStajalist(l);
			break;
		case 8: m.prolaziKrozDva();
			break;
		case 9: m.najviseZajednickih();
			break;
		case 10: m.najblizeStajaliste();
			break;
		case 11: m.brojZajednickihSvihLinija();
			break;
		case 12: m.linijeKojeProlazeKrozSt();
			break;
		case 13: cout << "Unesi sifru stajalista:" << endl; cin >> zone; s = m.dohvatiSt(zone);  m.svaSusednaStajalista(s);
			break;
		case 14: m.najmanjePresedanje();
			break;	
		case 15:    //cout << m.zadnjaTacka() << endl;
			break;
		case 16: m.testGraf();
			break;
		case 0: kraj = 0;
		default: cout << "Nedozvoljen izbor:\n" << endl;
		}
	}
}

