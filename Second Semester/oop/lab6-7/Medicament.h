#pragma once
#include <string>
#include <iostream>

using std::string;
using std::cout;

class Medicament {
private:
    std::string denumire;
    int pret;
    std::string producator;
    std::string substanta;

public:
    Medicament()=default;
    Medicament(const string n, int p, const string prod, const string subst) : denumire{n}, pret{p}, producator{prod},
    substanta{subst} {
    }


    std::string getDenumire() const {
        return denumire;
    }

    std::string getProducator() const {
        return producator;
    }

    std::string getSubstanta() const {
        return substanta;
    }

    int getPret() const  {
        return pret;
    }
};

/*
Compara dupa denumire
returneaza true daca p1.tip e mai mic decat p2.tip
*/
bool cmpDenumire(const Medicament& p1, const Medicament& p2);

/*
Compara dupa producator
returneaza true daca p1.specie e mai mic decat p2
*/
bool cmpProducator(const Medicament& p1, const Medicament& p2);