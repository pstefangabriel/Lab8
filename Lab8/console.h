#pragma once
#include "medserv.h"
#include "Medicament.h"

class Console {
private:
	MedServ& serv;

	void adauga();

	void adauga_in_reteta();

	void umple();
	
	void goleste();

	void export_to_CVS();

	void export_to_CVS_cos();

	void export_to_CVS_medicamet();
	
	void export_to_HTML();

	void report(const vector<MedDTO>& meds);

	void sterge();

	void modifica();

	void cauta();

	void tipareste(const vector<Medicament>& meds);
public:
	Console(MedServ& _serv) : serv{ _serv } {
	}


	void run();
};