#pragma once
#include "Medicament.h"
#include <string>
#include <map>
#include <vector>
using std::map;
using std::string;
using std::vector;


class Report {
private:
	map<string, MedDTO> all;
public:
	void add(const Medicament& med) {
		bool apare = false;
		for (auto it = all.begin(); it != all.end(); ++it) {
			if (it->first == med.get_denumire()) {
				apare = true;
				it->second.set_count(it->second.get_count() + 1);
			}
		}
		if (apare == false) {
			MedDTO meddto{ med.get_denumire(), 1 };
			all[meddto.get_denumire()] = meddto;
		}
	}

	vector<MedDTO> lista() const {
		vector<MedDTO> vect;
		for (auto it = all.begin(); it != all.end(); ++it) {
			vect.push_back(it->second);
		}

		return vect;
	}
};