#include "export.h"
#include "Medicament.h"
#include <fstream>
#include <string>
#include <vector>
using std::ofstream;
using std::ifstream;
using std::string;
using std::vector;


void exportToCVS_cos(const string& fName, const vector<Medicament>& meds) {
	ofstream out(fName);
	if (!out.is_open()) {
		throw MedException("Unable to open file:" + fName);
	}
	for (const auto& m : meds) {
		out << m.get_denumire() << ",";
		out << m.get_producator() << ",";
		out << m.get_substanta_activa() << ",";
		out << m.get_pret() << "\n";
	}
	out.close();
}

void exportToCVS_medicament(const string& fName, const Medicament& med) {
	ofstream out(fName);
	if (!out.is_open()) {
		throw MedException("Unable to open file:" + fName);
	}
	out << med.get_denumire() << ",";
	out << med.get_producator() << ",";
	out << med.get_substanta_activa() << ",";
	out << med.get_pret() << "\n";
	out.close();
}

void exportToHTML(const string& fName, const vector<Medicament>& meds) {
	ofstream out(fName);
	if (!out.is_open()) {
		throw MedException("Unable to open file:" + fName);
	}
	out << "<html><body>" << std::endl;
	out << "<table border=\"1\" style=\"width:100 % \">" << std::endl;
	for (const auto& m : meds) {
		out << "<tr>" << std::endl;
		out << "<td>" << m.get_denumire() << "</td>" << std::endl;
		out << "<td>" << m.get_producator() << "</td>" << std::endl;
		out << "<td>" << m.get_substanta_activa() << "</td>" << std::endl;
		out << "<td>" << m.get_pret() << "</td>" << std::endl;
		out << "</tr>" << std::endl;
	}
	out << "</table>" << std::endl;
	out << "</body></html>" << std::endl;
	out.close();
}