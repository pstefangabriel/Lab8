#include "RetMed.h"
#include <assert.h>


void RetMed::adauga(const Medicament& med) {
	all.push_back(med);
}


void RetMed::umple(int nr, vector<Medicament> meds) {
	std::shuffle(meds.begin(), meds.end(),
		std::default_random_engine(std::random_device{}()));
	while (all.size() < nr && meds.size() > 0) {
		all.push_back(meds.back());
		meds.pop_back();
	}
}


void teste_ret() {
	RetMed ret;
	Medicament med{ "ceva", "ter", "ere", 20 };
	ret.adauga(med);
	assert(ret.lista().size() == 1);
	ret.adauga(med);
	ret.adauga(med);
	RetMed ret_umple;
	ret_umple.umple(2, ret.lista());
	assert(ret_umple.lista().size() == 2);
	ret_umple.goleste();
	assert(ret_umple.lista().size() == 0);
}