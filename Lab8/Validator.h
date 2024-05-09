#pragma once
#include "Medicament.h"
#include <string>
#include <stdexcept>
#include <assert.h>

class Validator {
public:
    void validate(const std::string& denumire, const std::string& producator, const std::string& substanta_activa, double pret);
};

void test();