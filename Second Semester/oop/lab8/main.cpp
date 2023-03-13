#include "UI.h"
#include "Service.h"
#include "Repository.h"
#include "Validator.h"

void adaugaCateva(MedService& ctr){
    ctr.addMed("Nurofen", 25,  "MMM", "aa");
    ctr.addMed("Paracetamol", 10,  "FFF", "dd");
    ctr.addMed("Strepsils", 50,  "SSS", "bb");
    ctr.addMed("AAA", 100,  "MMM", "aa");
    ctr.addMed("BBB", 250,  "SSS", "bb");
    ctr.addMed("CCC", 15,  "FFF", "cc");
}

void testAll() {
    testeRepo();
    testCtr();
    testValidator();
}

int main() {
    testAll();

    MedicamentRepo rep;
    MedValidator val;
    Reteta re;
    MedService ctr{ rep,val };
    ServiceReteta ret{rep,re,val};
    adaugaCateva(ctr);//adaug cateva el
    ConsolUI ui{ ctr,ret };
    ui.start();
    return 0;
}
