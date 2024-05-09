#include "medrepo.h"
#include <assert.h>


int MedRepo::index(const string& den, const string& prod,
	const string& subst) {
	for (int i = 0; i < size(all); i++) {
		if (all[i].get_denumire() == den && all[i].get_producator() == prod
			&& all[i].get_substanta_activa() == subst) {
			return i;
		}
	}
	return -1;
}


void MedRepo::add(Medicament& m) {
	if (index(m.get_denumire(), m.get_producator(),
		m.get_substanta_activa()) == -1) {
		all.push_back(m);
	}
	else {
		throw MedException("Medicamentul exista deja!");
	}
}


const Medicament& MedRepo::get(const string& den, const string& prod,
	const string& subst) const {
	for (auto& m : all) {
		if (m.get_denumire() == den && m.get_producator() == prod
			&& m.get_substanta_activa() == subst) {
			return m;
		}
	}
	throw MedException("Nu exista medicamentul cautat!");
}


void MedRepo::del(const string& den, const string& prod,
	const string& subst) { // intreaba daca e ok, daca dai delete e 
	// fara const?
	int pozitia = index(den, prod, subst);
	vector<Medicament>::iterator it = all.begin();
	if (pozitia != -1) {
		all.erase(it + pozitia);
	}
}


void MedRepo::mod(const string& den, const string& prod,
	const string& subst, const Medicament& nou) {

	// trebuia sa folosesc mai mult iteratorul?
	int pozitie = index(den, prod, subst);
	if (pozitie != -1) {
		all[pozitie].set_denumire(nou.get_denumire());
		all[pozitie].set_producator(nou.get_producator());
		all[pozitie].set_substanta_activa(nou.get_producator());
		all[pozitie].set_pret(nou.get_pret());
		//all[pozitie] = nou;
	}
}


const vector<Medicament>& MedRepo::get_all() const {
	return all;
}


const Medicament& MedRepo::get(const string& den) const {
	for (auto& m : all) {
		if (m.get_denumire() == den) {
			return m;
		}
	}
	throw MedException("Nu exista medicamentul cautat!");
}


void teste_repo() {
	// de ce nu modifica si obiectele efectiv
	// gen modifica doar ce e in repo
	// dar in repo se retin referinte deci de ce nu se 
	// modifica si obiectele
	MedRepo rep;
	Medicament med2{ "idk", "smt", "ceva", 21.30 };
	rep.add(med2);
	assert(rep.get_all().size() == 1);
	assert(rep.get("idk", "smt", "ceva").get_pret() == 21.30);

	Medicament med{ "idk1", "sec", "ter", 30.6 };
	Medicament med3{ "idk2", "sec", "ter", 30.6 };
	rep.add(med);
	assert(rep.get_all().size() == 2);

	rep.del(med.get_denumire(), med.get_producator(),
		med.get_substanta_activa());
	assert(rep.get_all().size() == 1);
	//assert(med.get_denumire() == "idk1");

	rep.mod(med2.get_denumire(), med2.get_producator(),
		med2.get_substanta_activa(), med3);
	vector<Medicament> all = rep.get_all();
	assert(all[0].get_denumire() == "idk2");
	//assert(med2.get_denumire() == "idk2");
	try {
		rep.add(med2);
		rep.add(med2);
	}
	catch (MedException& e) {
		assert(e.getMsg() == "Medicamentul exista deja!");
	}
	try {
		rep.get("idk10", "sec", "ter");
	}
	catch (MedException& e) {
		assert(e.getMsg() == "Nu exista medicamentul cautat!");
	}
}