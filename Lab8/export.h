#pragma once
#include <string>
#include <vector>
#include "Medicament.h"
/*
Scrie in fisierul fName lista de meicamente
in format Comma Separated Values
arunca MedException daca nu poate crea fisierul
*/
void exportToCVS_cos(const std::string& fName, const std::vector<Medicament>& meds);

void exportToCVS_medicament(const std::string& fName, const Medicament& med);
/*
Scrie in fisierul fName lista de medicamente
in format HTML
arunca MedException daca nu poate crea fisierul
*/
void exportToHTML(const std::string& fName, const std::vector<Medicament>& meds);