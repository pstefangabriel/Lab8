#include "console.h"
#include "Medicament.h"
#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;


void Console::tipareste(const vector<Medicament>& meds) {
	for (const auto& m : meds) {
		cout << "Denumire : " << m.get_denumire() << " "
			<< "Producator : " << m.get_producator() << " "
			<< "Substanta activa : " << m.get_substanta_activa() << " "
			<< "Pret : " << m.get_pret() << "\n";
	}
	cout << endl;
}


void Console::adauga() {
	std::cin.get();
	string den, prod, subst;
	double pret;
	cout << "Denumire: "; std::getline(std::cin, den);
	cout << "Producator: "; std::getline(std::cin, prod);
	cout << "Substanta activa: "; std::getline(std::cin, subst);
	cout << "Pret: "; cin >> pret;
	try {
		serv.add_med(den, prod, subst, pret);
	}
	catch (MedException& e) {
		cout << e.getMsg();
	}
}


void Console::sterge() {
	string den, prod, subst;
	cout << "Denumire: "; cin >> den;
	cout << "Producator: "; cin >> prod;
	cout << "Substanta activa: "; cin >> subst;
	try {
		serv.del_med(den, prod, subst);
	}
	catch (MedException& e) {
		cout << e.getMsg();
	}
}


void Console::modifica() {
	string den, prod, subst, den_nou, prod_nou, subst_nou;
	double pret_nou;

	cout << "Denumire: "; cin >> den;
	cout << "Producator: "; cin >> prod;
	cout << "Substanta activa: "; cin >> subst;
	cout << "Denumire noua: "; cin >> den_nou;
	cout << "Producator nou: "; cin >> prod_nou;
	cout << "Substanta activa noua: "; cin >> subst_nou;
	cout << "Pret nou: "; cin >> pret_nou;
	try {
		serv.mod_med(den, prod, subst, den_nou, prod_nou, subst_nou, pret_nou);
	}
	catch (MedException& e) {
		cout << e.getMsg();
	}
}


void Console::cauta() {
	cout << "Denumire: "; string den; cin >> den;
	cout << "Producator: "; string prod; cin >> prod;
	cout << "Substanta activa: "; string subst; cin >> subst;
	try {
		Medicament m = serv.get(den, prod, subst);
		cout << "Denumire : " << m.get_denumire() << " "
			<< "Producator : " << m.get_producator() << " "
			<< "Substanta activa : " << m.get_substanta_activa() << " "
			<< "Pret : " << m.get_pret() << "\n";
	}
	catch (MedException& e) {
		cout << e.getMsg();
	}
}


void Console::adauga_in_reteta() {
	try {
		string denumire;
		cout << "Introduceti denumirea medicamentului : ";
		cin >> denumire;
		serv.add_in_reteta(denumire);
	}
	catch (MedException& e) {
		cout << e.getMsg();
	}
}


void Console::umple() {
	try {
		int cate;
		cout << "Introduceti numarul de medicamente : ";
		cin >> cate;
		serv.umple_reteta(cate);
	}
	catch (MedException& e) {
		cout << e.getMsg();
	}
}


void Console::goleste() {
	try {
		serv.goleste_reteta();
	}
	catch (MedException& e) {
		cout << e.getMsg();
	}
}


void Console::export_to_CVS_cos() {
	string fName;
	cout << "Introduceti numele fisierului : ";
	cin >> fName;
	serv.export_CVS_cos(fName);
}


void Console::export_to_CVS_medicamet() {
	string fName, denumire;
	cout << "Introduceti numele fisierului : ";
	cin >> fName;
	cout << "Introduceti denumirea : ";
	cin >> denumire;
	serv.export_CVS_medicament(fName, denumire);
}


void Console::export_to_HTML() {
	string fName;
	cout << "Introduceti numele fisierului : ";
	cin >> fName;
	serv.export_HTML(fName);
}


void Console::export_to_CVS() {
	int optiune;
	cout << "1). Exporta cos\n";
	cout << "2). Exporta medicament\n";
	cin >> optiune;
	if (optiune == 1) {
		export_to_CVS_cos();
	}
	else if (optiune == 2) {
		export_to_CVS_medicamet();
	}
}


void Console::report(const vector<MedDTO>& meds) {
	for (const auto& m : meds) {
		cout << "Denumire : " << m.get_denumire() << " "
			<< "Count : " << m.get_count() << "\n";
	}
	cout << endl;
}


void Console::run() {
	serv.add_med( "ceve", "ere", "ter", 10 );
	serv.add_med( "rtte", "rr", "tt", 20 );
	serv.add_med( "cderr", "popo", "popp", 30 );
	serv.add_med( "ceve", "ceva", "eee", 40 );
	serv.add_med( "fff", "ed", "ddd", 50 );
	serv.add_med( "ccc", "ee", "ddd", 60 );
	serv.add_med( "dune", "hm", "zar", 70 );
	serv.add_med( "ibuprofen", "hm", "zara", 80 );
	serv.add_med( "ddd", "ccc", "bbb", 90 );
	serv.add_med( "ceve", "ydfe", "aar", 100 );
	while (true) {
		string subst;
		tipareste(serv.get_reteta());
		cout << "1. Adauga\n";
		cout << "2. Sterge\n";
		cout << "3. Modifica\n";
		cout << "4. Cauta\n";
		cout << "5. Filtreaza dupa pret\n";
		cout << "6. Filtreaza dupa substanta activa\n";
		cout << "7. Sorteaza dupa denumire\n";
		cout << "8. Sorteaza dupa producator\n";
		cout << "9. Sorteaza dupa substanta activa si pret\n";
		cout << "10. Adauga in reteta\n";
		cout << "11. Umple reteta\n";
		cout << "12. Goleste reteta\n";
		cout << "13. Exporta CVS\n";
		cout << "14. Exporta HTML\n";
		cout << "15. Report\n";
		cout << "0. Quit\n";
		int opt; cin >> opt;
		switch (opt) {
		case 1:
			adauga();
			break;
		case 2:
			sterge();
			break;
		case 3:
			modifica();
			break;
		case 4:
			cauta();
			cout << endl;
			break;
		case 5:
			cout << "Pret: "; int pret; cin >> pret;
			tipareste(serv.filtreaza_pret(pret));
			cout << endl;
			break;
		case 6:
			cout << "Substanta activa: "; cin >> subst;
			tipareste(serv.filtreaza_substanta_activa(subst));
			cout << endl;
			break;
		case 7:
			tipareste(serv.sort_denumire());
			cout << endl;
			break;
		case 8:
			tipareste(serv.sort_producator());
			cout << endl;
			break;
		case 9:
			tipareste(serv.sort_subst_pret());
			cout << endl;
			break;
		case 10:
			adauga_in_reteta();
			break;
		case 11:
			umple();
			break;
		case 12:
			goleste();
			break;
		case 13:
			export_to_CVS();
			break;
		case 14:
			export_to_HTML();
			break;
		case 15:
			report(serv.afiseaza_report());
			break;
		case 0:
			return;
		}
	}
}