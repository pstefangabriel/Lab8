#include "Medicament.h"
#include <assert.h>


bool cmp_denumire(const Medicament& med1, const Medicament& med2) {
	return med1.get_denumire() < med2.get_denumire();
}


bool cmp_producator(const Medicament& med1, const Medicament& med2) {
	return med1.get_producator() < med2.get_producator();
}


void teste_medicament() {
	Medicament med{ "ceva", "idk", "smt", 32.7 };
	MedException ex{ "ceva" };

	assert(med.get_denumire() == "ceva");
	med.set_denumire("nou");
	assert(med.get_denumire() == "nou");
	assert(ex.getMsg() == "ceva");
}