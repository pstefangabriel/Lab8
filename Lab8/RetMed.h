#pragma once
#include <vector>
#include <string>
#include <random>
#include "medrepo.h"
using std::vector;
using std::string;


class RetMed {
	vector<Medicament> all;
public:
	RetMed() = default;

	void adauga(const Medicament& med);

	void goleste() {
		all.clear();
	}

	void umple(int nr, vector<Medicament> meds);

	const vector<Medicament>& lista() const {
		return all;
	}
};

void teste_ret();