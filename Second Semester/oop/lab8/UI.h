//
// Created by Eveline Molnar on 21.04.2022.
//
#pragma once
#include "Service.h"
#include "Medicament.h"
class ConsolUI {
    MedService& ctr;
    ServiceReteta& ret;
    /*
    Citeste datele de la tastatura si adauga Masina
    arunca exceptie daca: nu se poate salva, nu e valida
    */
    void adaugaUI();

    /*
    Citeste id-ul de la tastatura si sterge Masina
    arunca exceptie daca: nu exista masina cautata
    */
    void stergeUI();

    /*
    Citeste id-ul de la tastatura si modifica Masina
    arunca exceptie daca: nu exista masina cautata
    */
    void modificaUI();

    /*
    Citeste id-ul de la tastatura si cauta Masina
    arunca exceptie daca: nu exista masina cautata
    */
    //void cautaUI();

    void filtrareUI();

    void filtrare2UI();

    //void sortUI();

    /*
    Tipareste o lista de masini la consola
    */
    static void tipareste(const vector<Medicament>& Medicamente);

    void addRetetaUI();
    void clearRetetaUI();
    void addRandomUI();
    void batch_mode();
    //void exportt();

public:
    ConsolUI(MedService& ctr, ServiceReteta& ret) :ctr{ ctr }, ret{ ret }{
    }
    //nu permitem copierea obiectelor
    ConsolUI(const ConsolUI& ot) = delete;

    void start();
};
