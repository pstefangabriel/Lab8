#include "Validator.h"

void Validator::validate(const std::string& denumire, const std::string& producator, const std::string& substanta_activa, double pret) {
	if (denumire.empty()) {
		throw MedException("Denumire cannot be empty");
	}
	if (producator.empty()) {
		throw MedException("Producator cannot be empty");
	}
	if (substanta_activa.empty()) {
		throw MedException("Substanta_activa cannot be empty");
	}
	if (pret < 0) {
		throw MedException("Pret cannot be negative");
	}
}

void test() {
	Validator v;
	v.validate("Nurofen", "Reckitt Benckiser", "Ibuprofen", 10);
	try {
		v.validate("", "Reckitt Benckiser", "Ibuprofen", 10);
		assert(false);
	}
	catch (MedException) {
		assert(true);
	}
	try {
		v.validate("Nurofen", "", "Ibuprofen", 10);
		assert(false);
	}
	catch (MedException) {
		assert(true);
	}
	try {
		v.validate("Nurofen", "Reckitt Benckiser", "", 10);
		assert(false);
	}
	catch (MedException) {
		assert(true);
	}
	try {
		v.validate("Nurofen", "Reckitt Benckiser", "Ibuprofen", -10);
		assert(false);
	}
	catch (MedException) {
		assert(true);
	}
}