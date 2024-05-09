#pragma once
#include "Medicament.h"
#include <vector>
#include <string>
#include <ostream>
using std::vector;
using std::string;
using std::ostream;


class MedRepo {

private:
	vector<Medicament> all;


public:
	MedRepo() = default;


	// nu permitem copiere de obiecte
	MedRepo(const MedRepo& o) = delete;


	int index(const string& den, const string& prod,
		const string& subst);


	void add(Medicament& m);


	void del(const string& den, const string& prod,
		const string& subst);


	void mod(const string& den, const string& prod,
		const string& subst, const Medicament& nou);


	const Medicament& get(const string& den, const string& prod,
		const string& subst) const;


	const Medicament& get(const string& den) const;


	const vector<Medicament>& get_all() const;
};


void teste_repo();