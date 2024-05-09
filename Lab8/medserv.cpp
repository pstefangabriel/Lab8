#include "medserv.h"
#include <assert.h>
#include <fstream>


vector<Medicament> MedServ::filtreaza(function<bool(const Medicament&)> fct) {
	vector<Medicament> rez;
	for (const auto& med : repo.get_all()) {
		if (fct(med)) {
			rez.push_back(med);
		}
	}

	return rez;
}


vector<Medicament> MedServ::general_sort(function<bool(const Medicament&, const Medicament&)> fct) {
	vector<Medicament> rez{ repo.get_all() };
	for (int i = 0; i < rez.size() - 1; i++) {
		for (int j = i + 1; j < rez.size(); j++) {
			if (!fct(rez[i], rez[j])) {
				Medicament aux = rez[i];
				rez[i] = rez[j];
				rez[j] = aux;
			}
		}
	}

	return rez;
}


vector<Medicament> MedServ::filtreaza_pret(int pret) {
	return filtreaza([pret](const Medicament& med) {
		return med.get_pret() == pret;
		});
}


vector<Medicament> MedServ::filtreaza_substanta_activa(string subst) {
	return filtreaza([subst](const Medicament& med) {
		return med.get_substanta_activa() == subst;
		});
}


vector<Medicament> MedServ::sort_denumire() {
	return general_sort(cmp_denumire);
}


vector<Medicament> MedServ::sort_producator() {
	return general_sort(cmp_producator);
}


vector<Medicament> MedServ::sort_subst_pret() {
	return general_sort([](const Medicament& med1, const Medicament& med2) {
		if (med1.get_substanta_activa() == med2.get_substanta_activa()) {
			return med1.get_pret() < med2.get_pret();
		}
		return med1.get_substanta_activa() < med2.get_substanta_activa();
		});
}


void MedServ::add_med(const string& d, const string& p,
	const string& s, double _pret) {
	Medicament med{ d, p, s, _pret };
	val.validate(d, p, s, _pret);
	repo.add(med);
	rep.add(med);
}


void MedServ::del_med(const string& d, const string& p, const string& s) {
	repo.get(d, p, s);
	repo.del(d, p, s);
}


void MedServ::mod_med(const string& d, const string& p,
	const string& s, const string& d_nou, const string& p_nou,
	const string& s_nou, double pret_nou) {
	Medicament med{ d_nou, p_nou, s_nou, pret_nou };
	val.validate(d_nou, p_nou, s_nou, pret_nou);
	repo.get(d, p, s);
	repo.mod(d, p, s, med);
}


void MedServ::add_in_reteta(const string& den) {
	//Medicament med = repo.get(den);
	ret.adauga(repo.get(den));
}


void MedServ::umple_reteta(int cate) {
	ret.umple(cate, repo.get_all());
}


void MedServ::goleste_reteta() {
	ret.goleste();
}


vector<Medicament> MedServ::get_reteta() {
	return ret.lista();
}


void MedServ::export_CVS_cos(string fName) const{
	exportToCVS_cos(fName, ret.lista());
}

void MedServ::export_CVS_medicament(string fName, const string& denumire) const {
	exportToCVS_medicament(fName, repo.get(denumire));
}

void MedServ::export_HTML(string fName) const{
	exportToHTML(fName, ret.lista());
}

vector<MedDTO> MedServ::afiseaza_report() const {
	return rep.lista();
}

void test_add_med() {
	MedRepo repo;
	Validator val;
	MedServ serv{ repo, val };
	serv.add_med("paracetamol", "Zentiva", "paracetamol", 10);
	assert(serv.get_all().size() == 1);
}


void test_del_med() {
	MedRepo repo;
	Validator val;
	MedServ serv{ repo, val };
	serv.add_med("paracetamol", "Zentiva", "paracetamol", 10);
	serv.del_med("paracetamol", "Zentiva", "paracetamol");
	assert(serv.get_all().size() == 0);
}


void test_mod_med() {
	MedRepo repo;
	Validator val;
	MedServ serv{ repo, val };
	serv.add_med("paracetamol", "Zentiva", "paracetamol", 10);
	serv.mod_med("paracetamol", "Zentiva", "paracetamol", "paracetamol", "Zentiva", "paracetamol", 20);
	vector<Medicament> ceva = serv.get_all();
	assert(ceva[0].get_pret() == 20);
}


void test_filtreaza_pret() {
	MedRepo repo;
	Validator val;
	MedServ serv{ repo, val };
	serv.add_med("paracetamol", "Zentiva", "paracetamol", 10);
	serv.add_med("paracetamol", "Zentiv", "paracetamol", 20);
	serv.add_med("paracetamol", "Zenti", "paracetamol", 30);
	vector<Medicament> rez = serv.filtreaza_pret(20);
	assert(rez.size() == 1);
}


void test_filtreaza_substanta_activa() {
	MedRepo repo;
	Validator val;
	MedServ serv{ repo, val };
	serv.add_med("paracetamol", "Zentiva", "paracetamol", 10);
	serv.add_med("paracetamol", "Zentiv", "paracetamol", 20);
	serv.add_med("paracetamol", "Zenti", "paracetamol", 30);
	vector<Medicament> rez = serv.filtreaza_substanta_activa("paracetamol");
	assert(rez.size() == 3);
}


void test_sort_denumire() {
	MedRepo repo;
	Validator val;
	MedServ serv{ repo, val };
	serv.add_med("paracetamol", "Zentiva", "paracetamol", 10);
	serv.add_med("aspirina", "Zentiva", "paracetamol", 20);
	serv.add_med("ibuprofen", "Zentiva", "paracetamol", 30);
	vector<Medicament> rez = serv.sort_denumire();
	assert(rez[0].get_denumire() == "aspirina");
	assert(rez[1].get_denumire() == "ibuprofen");
	assert(rez[2].get_denumire() == "paracetamol");
	serv.add_in_reteta("paracetamol");
	serv.goleste_reteta();
	serv.get_reteta();
	serv.afiseaza_report();
}


void test_sort_subst_pret() {
	MedRepo repo;
	Validator val;
	MedServ serv{ repo, val };
	serv.add_med("paracetamol", "Zentiva", "paracetamol", 30);
	serv.add_med("aspirina", "Zentiva", "paracetamola", 10);
	serv.add_med("ibuprofen", "Zentiva", "paracetamol", 20);
	vector<Medicament> rez = serv.sort_subst_pret();
	assert(rez[2].get_denumire() == "aspirina");
	assert(rez[0].get_denumire() == "ibuprofen");
	assert(rez[1].get_denumire() == "paracetamol");
}


void test_sort_producator() {
	MedRepo repo;
	Validator val;
	MedServ serv{ repo, val };
	serv.add_med("paracetamol", "centiva", "paracetamol", 30);
	serv.add_med("aspirina", "aentiva", "paracetamol", 10);
	serv.add_med("ibuprofen", "bentiva", "paracetamol", 20);
	vector<Medicament> rez = serv.sort_producator();
	assert(rez[0].get_denumire() == "aspirina");
	assert(rez[1].get_denumire() == "ibuprofen");
	assert(rez[2].get_denumire() == "paracetamol");
}


void test_get() {
	MedRepo repo;
	Validator val;
	MedServ serv{ repo, val };
	serv.add_med("paracetamol", "centiva", "paracetamol", 30);
	Medicament med = serv.get("paracetamol", "centiva", "paracetamol");
	assert(med.get_denumire() == repo.get("paracetamol", "centiva", "paracetamol").get_denumire());
}


void test_export() {
	MedRepo rep;
	Validator val;
	MedServ ctr{ rep, val };
	ctr.add_med("aaa", "bbb", "ccc", 10);
	ctr.add_med("ccc", "bbb", "ddd", 20);
	ctr.add_med("bbb", "bbb", "eee", 30);
	ctr.umple_reteta(3);
	ctr.export_CVS_cos("testExport.cvs");
	std::ifstream in("testExport.cvs");
	assert(in.is_open());
	int countLines = 0;
	while (!in.eof()) {
		string line;
		in >> line;
		countLines++;
	}
	in.close();
	assert(countLines == 4);//avem o linie pentru fiecare pet + o linie goala
	// la fel si pt cvs medicament, html
	ctr.export_CVS_medicament("testt", "aaa");
	ctr.export_HTML("testExport.html");
	try {
		ctr.export_CVS_medicament("test/Export.cvs/", "ceva");
	}
	catch (MedException&) {
		assert(true);
	}
	try {
		ctr.export_HTML("a/b/c/Export.html");
	}
	catch (MedException&) {
		assert(true);
	}
	try {
		ctr.export_CVS_cos("test/Export.cvs");
	}
	catch (MedException&) {
		assert(true);
	}
}


void teste_serv() {
	test_add_med();
	test_del_med();
	test_mod_med();
	test_filtreaza_pret();
	test_filtreaza_substanta_activa();
	test_sort_denumire();
	test_sort_producator();
	test_sort_subst_pret();
	test_get();
	test_export();
}