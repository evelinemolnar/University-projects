//
// Created by Eveline Molnar on 21.04.2022.
//
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
    Medicament(const string n, int p, const string prod, const string subst) : denumire{n}, pret{p}, producator{prod},
                                                                               substanta{subst} {
    }


    string getDenumire() const {
        return denumire;
    }

    string getProducator() const {
        return producator;
    }

    string getSubstanta() const {
        return substanta;
    }

    int getPret() const  {
        return pret;
    }
};

bool cmpDenumire(const Medicament& p1, const Medicament& p2);

bool cmpProducator(const Medicament& p1, const Medicament& p2);
