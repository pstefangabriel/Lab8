#include <iostream>
#include "Console.h"
#include "Medicament.h"
#include "medrepo.h"
#include "medserv.h"
#include "Validator.h"
#include "RetMed.h"


void teste() {
    teste_medicament();
    teste_repo();
    teste_serv();
    test();
    teste_ret();
}


int main() {
    teste();
    MedRepo repo;
    Validator val;
    MedServ serv(repo, val);
    Console cons(serv);
    cons.run();

    return 0;
}

