#pragma once
#include "Service.h"
#include "Medicament.h"
class ConsolUI {
    MedService &ctr;

    /*
    Citeste datele de la tastatura si adauga Medicament
    arunca exceptie daca: nu se poate salva, nu e valid
    */
    void adaugaUI();


    void stergeUI();

    void modificaUI();

    //void cautaUI();

    void sortUI();

    void tipareste(const DynamicVector<Medicament> &meds);

    void filtrareUI();

    void filtrare2UI();

public:
    ConsolUI(MedService &ctr) : ctr{ctr} {
    }

    //nu permitem copierea obiectelor
    ConsolUI(const ConsolUI &ot) = delete;

    void start();
};