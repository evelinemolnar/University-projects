#pragma once

#include "Medicament.h"
#include "Repository.h"
#include <string>
#include <vector>

#include <functional>
#include "Validator.h"

using std::vector;
using std::function;

class MedService {
    MedicamentRepo& rep;
    MedValidator& val;

    /*
     Functie de sortare generala
     maiMareF - functie care compara 2 Pet, verifica daca are loc relatia mai mare
              - poate fi orice functe (in afara clasei) care respecta signatura (returneaza bool are 2 parametrii Pet)
              - poate fi functie lambda (care nu capteaza nimic in capture list)
     returneaza o lista sortata dupa criteriu dat ca paramatru
    */
    //vector<Medicament> generalSort(bool (*maiMicF)(const Medicament&, const Medicament&));
    /*
    Functie generala de filtrare
    fct - poate fi o functie
    fct - poate fi lambda, am folosit function<> pentru a permite si functii lambda care au ceva in capture list
    returneaza doar animalele care trec de filtru (fct(pet)==true)
    */
    vector<Medicament> filtreaza(function<bool(const Medicament&)> fct);
public:
    MedService(MedicamentRepo& rep, MedValidator& val) :rep{ rep }, val{ val } {
    }
    //nu permitem copierea de obiecte PetStore
    MedService(const MedService& ot) = delete;
    /*
     returneaza toate animalele in ordinea in care au fost adaugate
    */
    const vector<Medicament>& getAll() noexcept {
        return rep.getAll();
    }
    /*
    Adauga un nou pet
    arunca exceptie daca: nu se poate salva, nu este valid
    */
    void addMed(const string& denumire, int pret, const string& producator, const string& substanta);

    /*
    Sorteaza dupa tip
    */
    void deleteMed(const string& denumire);

    void updateMed(const string& denumire, int pret, const string& producator, const string& substanta);

    void cautaMed(const string& denumire);

    vector<Medicament> sort(function<bool(const Medicament& m1, const Medicament& m2)>compareFunction) const;

    vector<Medicament> sortByDenumire();

    /*
    Sorteaza dupa prod
    */
    vector<Medicament> sortByProducator();


    /*
    Sorteaza dupa subst+pret
    */
    //vector<Medicament> sortBySubstPret();

    vector<Medicament> filtrarePret(int pretMin, int pretMax);

    vector<Medicament> filtrareSubstanta(const string& subst);

};
void testCtr();

class ServiceReteta{
private:
    MedicamentRepo& rep;
    Reteta& ret;
    MedValidator& val;
public:
    ServiceReteta(MedicamentRepo& _rep, Reteta& _ret, MedValidator& _val):rep{ _rep }, ret{ _ret }, val{ _val }{}

    void addReteta(const std::string&);
    void clearRetServ();
    const std::vector<Medicament>& srv_getReteta() const;
    void addMedRet(const string& denumire, int pret, const string& producator, const string& substanta);
    size_t numar_medSRV();
    int addRandom(int NumberofMeds);
};

