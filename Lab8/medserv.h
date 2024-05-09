#pragma once
#include "medrepo.h"
#include "Validator.h"
#include "RetMed.h"
#include "export.h"
#include <string>
#include <vector>
#include <functional>
#include "Report.h"
using std::vector;
using std::string;
using std::function;


class MedServ {

private:
	MedRepo& repo;
	Validator& val;
	RetMed ret;
	Report rep;


	vector<Medicament> filtreaza(function<bool(const Medicament&)> fct);


	vector<Medicament> general_sort(function<bool(const Medicament&, const Medicament&)> fct);

public:
	MedServ(MedRepo& rep, Validator& _val) : repo{ rep }, val{ _val } {}


	const vector<Medicament>& get_all() const {
		return repo.get_all();
	}


	const Medicament& get(const string& den, const string& prod,
		const string& subst) const {
		return repo.get(den, prod, subst);
	}


	void add_med(const string& d, const string& p,
		const string& s, double _pret);


	void del_med(const string& d, const string& p, const string& s);


	void mod_med(const string& d, const string& p,
		const string& s, const string& d_nou, const string& p_nou,
		const string& s_nou, double pret_nou);


	void add_in_reteta(const string& den);


	void umple_reteta(int cate);


	void goleste_reteta();


	vector<Medicament> filtreaza_pret(int pret);


	vector<Medicament> filtreaza_substanta_activa(string subst);


	vector<Medicament> sort_denumire();


	vector<Medicament> sort_producator();


	vector<Medicament> sort_subst_pret();

	vector<Medicament> get_reteta();

	void export_CVS_cos(string fName) const;

	void export_CVS_medicament(string fName, const string& denumire) const;

	void export_HTML(string fName) const;

	vector<MedDTO> afiseaza_report() const;
};


void teste_serv();