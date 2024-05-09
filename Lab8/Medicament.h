#pragma once
#include <string>
#include <iostream>
using std::string;
using std::cout;


class MedException {
	string msg;
public:
	MedException(const string& m) :msg{ m } {};
	string getMsg()const { return msg; }
};


class MedDTO {
private:
	string denumire;
	int count;
public:
	MedDTO(const string den, int c) : denumire{ den }, count{ c } {
	}

	MedDTO() : denumire{ "" }, count{ 0 } {
	}

	string get_denumire() const {
		return denumire;
	}

	int get_count() const {
		return count;
	}

	void set_count(int nr) {
		count = nr;
	}

	~MedDTO() = default;
};


class Medicament {

private:
	string denumire, producator, substanta_activa;
	double pret;

public:
	Medicament(const string d, const string p, const string s,
		double _pret) : denumire{ d }, producator{ p }, substanta_activa{ s }, pret{ _pret } {
	}


	Medicament(const Medicament& other) {
		this->denumire = other.denumire;
		this->producator = other.producator;
		this->substanta_activa = other.substanta_activa;
		this->pret = other.pret;
		cout << "*\n";
	}


	string get_denumire() const {
		return denumire;
	}


	string get_producator() const {
		return producator;
	}


	string get_substanta_activa() const {
		return substanta_activa;
	}


	double get_pret() const {
		return pret;
	}


	void set_denumire(const string& _denumire) {
		denumire = _denumire;
	}


	void set_producator(const string& _producator) {
		producator = _producator;
	}


	void set_substanta_activa(const string& _subst) {
		substanta_activa = _subst;
	}


	void set_pret(double _pret) {
		pret = _pret;
	}


	~Medicament() = default;
};


void teste_medicament();


bool cmp_denumire(const Medicament& med1, const Medicament& med2);


bool cmp_producator(const Medicament& med1, const Medicament& med2);