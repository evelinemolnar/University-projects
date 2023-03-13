//
// Created by Eveline Molnar on 21.04.2022.
//

#include "UI.h"
#include "Medicament.h"
#include <iostream>
#include <string>

using namespace std;

using std::cout;
using std::cin;

void ConsolUI::tipareste(const vector<Medicament>& meds) {
    cout << "Medicamente:\n";
    for (const auto& med : meds) {
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
    if(den.empty()||pret.empty()||prod.empty()||sub.empty()) {
        cout << "Date invalide!\n";
        return;
    }
    int pretint ;
    if (pret.size() > 16)
        cout << "Pret prea mare.";
    else {
        try {
            for (char i : pret)
                if (i < '0' || i > '9')
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
    if(den.empty()) {
        cout << "Denumire invalida!\n";
        return;
    }
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
    if(den.empty()||pret.empty()||prod.empty()||sub.empty()) {
        cout << "Date invalide!\n";
        return;
    }
    if (pret.size() > 16)
        cout << "Pret prea mare.";
    else {
        try {
            for (char i : pret)
                if (i < '0' || i > '9')
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

void ConsolUI::addRetetaUI() {
    string den;
    cout<<"Introduceti denumirea: \n";
    getline(cin, den);
    try{
        ret.addReteta(den);
        cout<<"Adaugat cu succes\n";

    }
    catch (const MedRepoException& ex) {
        cout << ex << "\n";
    }
}

void ConsolUI::clearRetetaUI() {
    ret.clearRetServ();
    cout<<"Reteta este goala\n";
}

void ConsolUI::addRandomUI()
{

    cout << "Cate medicamente doriti sa adaugati?\n";
    string numar;
    int numar_int ;
    getline(cin, numar);
    if (numar.length() > 4)
    {
        cout << "Ati introdus un numar prea mare!\n";
    }
    else {
        try {
            numar_int = stoi(numar);
        }
        catch (const exception&) {
            cout << "Id-ul este invalid!\n";
            return;
        }

        try {
            int cate = ret.addRandom(numar_int);
            cout << "S-au adaugat " << cate << " masini!\n";
        }
        catch (const exception& ex) {
            cout << ex.what();
        }

    }
}


void ConsolUI::filtrareUI() {
    int  pretmax_int = 0;
    int pretmin_int =0;
    string pretMin;
    cout<<"Dati pret minim:";
    getline(cin, pretMin);
    string pretMax;
    cout<<"Dati pret max:";
    getline(cin, pretMax);
    if (pretMin.size() < 16) {
        pretmin_int = stoi(pretMin);
    }
    tipareste(ctr.filtrarePret(pretmin_int, pretmax_int));

}

void ConsolUI::filtrare2UI() {
    string sub;
    cout<<"Dati sub:";
    getline(cin, sub);
    tipareste(ctr.filtrareSubstanta(sub));
}
/*
void ConsolUI::exportt()
{
    fstream fout;
    vector < Medicament > meds = ret.getReteta();
    size_t length = meds.size();
    string fileName = "";
    string path = "fisiere_pt_export/";

    while (fileName == "")
    {
        cout << "Numele fisierului pentru export: ";
        getline(cin, fileName);
    }

    path = path + fileName + ".csv";

    fout.open(path, std::ios::out, std::ios::trunc);
    fout.close();
    fout.open(path, std::ios::out | std::ios::app);

    vector<Medicament>v = ret.getReteta();
    for (const auto& medi : v) {
        fout << "DENUMIRE: " << medi.getDenumire() << "|| PRET: " << medi.getPret() << " || PRODUCATOR: " << medi.getProducator() << " ||  SUBSTANTA:" << medi.getSubstanta()<<  "\n";
    }
    cout << "Export cu succes!\n";
}*/


void ConsolUI::batch_mode()
{
    vector<string>comenzi;
    string delim = " ";

    comenzi.emplace_back("add nume 20 prod subst ");
    comenzi.emplace_back("update nume 50 prod2 subst2 ");
    comenzi.emplace_back("del Nurofen ");

    vector<string> words;
    for (auto comanda : comenzi) {
        size_t pos ;
        words.clear();

        while ((pos = comanda.find(delim)) != string::npos) {
            words.push_back(comanda.substr(0, pos));
            comanda.erase(0, pos + delim.length());
        }

        if (words[0] == "add") {

            if (words.size() == 6)
                try {
                    int pret = stoi(words[2]);
                    ctr.addMed(words[1], pret, words[3], words[4]);

                }
                catch (const MedRepoException& ex) {
                    cout << ex<<"\n";
                }

        }
        else if (words[0] == "update") {
            if (words.size() == 6)
                try {
                    ctr.updateMed(words[1], stoi(words[2]), words[3], words[4]);

                }
                catch (const MedRepoException& ex) {
                    cout << ex<<"\n";
                }
        }
        else if (words[0] == "del") {
            if (words.size() == 2)
                try {
                    ctr.deleteMed(words[1]);
                }
                catch (const MedRepoException& ex) {
                    cout << ex<<"\n";
                }
        }
        else cout << "Comanda invalida!\n";
    }
}


void ConsolUI::start() {



    while (true) {
        cout << "Meniu:\n";
        cout<< "1 Adaugare\n2 Tiparire\n3 Stergere\n4 Modificare\n5 Sortare\n6 Filtrare pret\n7 Filtrare subst activa\n8 Adauga la reteta\n9 Goleste reteta\n10 Genereaza random \n11 Batch-mode \n12 afiseaza\n0 Iesire\nDati comanda:";
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
        //else if (cmd == "5")
            //sortUI();
        else if (cmd == "6")
            filtrareUI();
        else if (cmd == "7")
            filtrare2UI();
        else if(cmd == "8")
            addRetetaUI();
        else if(cmd == "9")
            clearRetetaUI();
        else if(cmd == "10")
            addRandomUI();
        else if(cmd == "11")
            batch_mode();
        else if(cmd == "12")
            tipareste(ret.srv_getReteta());
        else if (cmd == "0")
            return;
        else
            cout << "Comanda invalida.\n";


    }
}