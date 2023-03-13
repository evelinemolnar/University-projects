#include "Console.h"
#include "Medicament.h"
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::istream;

void ConsolUI::sortUI()
{
    string cmd;
    cout << "Sortare dupa: 1.denumire 2. producator 3.subst+pret\n";
    cin >> cmd;

    if (cmd == "1") {
        DynamicVector<Medicament>v = ctr.sort([](const Medicament& m1, const Medicament& m2) {if (m1.getDenumire() < m2.getDenumire()) return true; else return false; });

        for (const auto& el : v)
            cout << el.getDenumire() << " " << el.getPret() << " " << el.getProducator() << " " << el.getSubstanta() << '\n';


    }
    else if (cmd == "2") {
        DynamicVector<Medicament>v = ctr.sort([](const Medicament& m1, const Medicament& m2) {if (m1.getProducator() < m2.getProducator()) return true; else return false; });
        for (const auto& el : v)
            cout << el.getDenumire() << " " << el.getPret() << " " << el.getProducator() << " " << el.getSubstanta() << '\n';

    }
    else if (cmd == "3") {
        DynamicVector<Medicament>v = ctr.sort([](const Medicament& m1, const Medicament& m2) {
            if (m1.getSubstanta() < m2.getSubstanta())
                return true;
            else if (m1.getSubstanta() == m2.getSubstanta())
                if (m1.getPret() < m2.getPret())
                    return true;
                else return false;
            else return false;
        });
        for (const auto& el : v)
            cout << el.getDenumire() << " " << el.getPret() << " " << el.getProducator() << " " << el.getSubstanta() << '\n';

    }
    else cout << "Comanda invalida\n";
}

void ConsolUI::tipareste(const DynamicVector<Medicament>& meds) {
    cout << "Medicamente:\n";
    DynamicVector<Medicament> v1;
    v1 = meds;
    for (const auto& med : v1) {
        cout << "DENUMIRE: " << med.getDenumire() << "|| PRET: " << med.getPret() << " || PRODUCATOR: " << med.getProducator() << " ||  SUBSTANTA:" << med.getSubstanta()<<  "\n";
    }
}

void ConsolUI::adaugaUI() {

    string den, pret, prod, sub;
    cout << "Dati denumire:";
    getline(cin, den);
    cout << "Dati pret:";
    getline(cin, pret);
    cout << "Dati prod:";
    getline(cin, prod);
    cout << "Dati sub:";
    getline(cin, sub);
    int pretint ;
    if (pret.size() > 16)
        cout << "Pret prea mare.";
    else {
        try {
            for (int i = 0; i < pret.size(); i++)
                if (pret[i] < '0' || pret[i] > '9')
                    throw string("Pret invalid!\n");
        }
        catch (string s) {
            cout << s;
            return;
        }
        pretint = stoi(pret);
        try {
            ctr.addMed(den, pretint, prod, sub);
            cout << "Adaugata cu succes\n";
        }
        catch (const MedRepoException &ex) {
            cout << ex << "\n";
        }
        catch (const ValidateException &e) {
            cout << e << "\n";
        }

    }
}


void ConsolUI::stergeUI() {
    string den;
    cout<<"Dati denumire:";
    getline(cin, den);
    try {
        ctr.deleteMed(den);
        cout << "Sters cu succes\n";
    }
    catch (const MedRepoException &ex){
        cout << ex << "\n";
    }
}

void ConsolUI::modificaUI() {
    string den, pret, prod, sub;
    cout<<"Dati denumire:";
    getline(cin, den);
    cout<<"Dati pret:";
    getline(cin, pret);
    cout<<"Dati prod:";
    getline(cin, prod);
    cout<<"Dati sub:";
    getline(cin, sub);
    int pretint;
    if (pret.size() > 16)
        cout << "Pret prea mare.";
    else {
        try {
            for (int i = 0; i < pret.size(); i++)
                if (pret[i] < '0' || pret[i] > '9')
                    throw string("Pret invalid!\n");
        }
        catch (string s) {
            cout << s;
            return;
        }
        pretint = stoi(pret);
        try {
            ctr.updateMed(den, pretint, prod, sub);
            cout << "Adaugata cu succes\n";
        }
        catch (const MedRepoException &ex) {
            cout << ex << "\n";
        }

    }
}


void ConsolUI::filtrareUI() {

    int pretmin_int =0;
    string pretMin;
    cout<<"Dati pret :";
    getline(cin, pretMin);
    if (pretMin.size() < 16) {
        pretmin_int = stoi(pretMin);
    }
    tipareste(ctr.filtrarePret(pretmin_int));

}

void ConsolUI::filtrare2UI() {
    string sub;
    cout<<"Dati sub:";
    getline(cin, sub);
    tipareste(ctr.filtrareSubstanta(sub));
}

void ConsolUI::start() {
    while (true) {
        cout << "Meniu:\n";
        cout
                << "1 Adaugare\n2 Tiparire\n3 Stergere\n4 Modificare\n5 Sortare\n6 Filtrare pret\n7 Filtrare subst activa\n0 Iesire\nDati comanda:";
        string cmd;
        getline(cin, cmd);
        if (cmd == "1")
            adaugaUI();
        else if (cmd == "2")
            tipareste(ctr.getAll());
        else if (cmd == "3")
            stergeUI();
        else if (cmd == "4")
            modificaUI();
        else if (cmd == "5")
            sortUI();
        else if (cmd == "6")
            filtrareUI();
        else if (cmd == "7")
            filtrare2UI();
        else if (cmd == "0")
            return;
        else
            cout << "Comanda invalida.\n";


    }
}