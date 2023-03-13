#include "Service.h"
#include <functional>
#include <cassert>

/*
vector<Medicament> MedService::generalSort(bool(*maiMicF)(const Medicament&, const Medicament&)) {
    vector<Medicament> v{ rep.getAll() };//fac o copie
    for (size_t i = 0; i < v.size(); i++) {
        for (size_t j = i + 1; j < v.size(); j++) {
            if (!maiMicF(v[i], v[j])) {Medicament aux = v[i];v[i] = v[j];v[j] =  aux;}
        }
    }
    return v;
}
*/

void MedService::addMed(const string& denumire, int pret,  const string& producator, const string& substanta) {
    Medicament p{ denumire, pret, producator, substanta };
    val.validate(p);
    rep.store(p);
}

/*
Sorteaza dupa tip
*/
void MedService::deleteMed(const string &denumire) {
    rep.del(denumire);
}

void MedService::updateMed(const string& denumire, int pret, const string& producator, const string& substanta){
    Medicament p{ denumire, pret, producator, substanta };
    rep.update(p);
}

void MedService::cautaMed(const string &denumire)  {
    rep.find(denumire);
}

DynamicVector<Medicament> MedService::sort(function<bool(const Medicament& m1, const Medicament& m2)>compareFunction) const
{
    DynamicVector<Medicament>v = rep.getAll();
    for (auto& el1 : v)
        for (auto& el2 : v)
            if (compareFunction(el1, el2))
            {
                Medicament aux = el1;
                el1 = el2;
                el2 = aux;
            }
    return v;
}

DynamicVector<Medicament> MedService::filtrarePret(int pret) {
    return filtreaza([pret](const Medicament& p) {
        return p.getPret() ==pret;
    });
}

DynamicVector<Medicament> MedService::filtrareSubstanta(const string &subst)  {
    return filtreaza([subst](const Medicament& m) {
        return m.getSubstanta() == subst;
    });
}

DynamicVector<Medicament> MedService::filtreaza(function<bool(const Medicament&)> fct){
    DynamicVector<Medicament> rez;
    DynamicVector<Medicament> v1;
    v1 = rep.getAll();
    for (const auto& Med : v1) {
        if (fct(Med)) {
            rez.add(Med);
        }
    }
    return rez;
}


void testAdaugaCtr() {
    MedicamentRepo rep;
    MedValidator val;
    MedService ctr{ rep,val };
    ctr.addMed("a",6 ,"a", "a");
    assert(ctr.getAll().size() == 1);

    //adaug ceva invalid
    try {
        ctr.addMed("", -1, "", "");
        assert(false);
    }
    catch (ValidateException&) {
        assert(true);
    }

}

void testStergeCtr() {
    MedicamentRepo rep;
    MedValidator val;
    MedService ctr{ rep,val };
    ctr.addMed("a",6 ,"a", "a");
    ctr.addMed("b",6 ,"b", "b");
    assert(ctr.getAll().size() == 2);
    ctr.deleteMed("b");
    assert(ctr.getAll().size() == 1);
}

void testModificaCtr() {
    MedicamentRepo rep;
    MedValidator val;
    MedService ctr{ rep,val };
    ctr.addMed("a",6 ,"a", "a");
    ctr.addMed("b",6 ,"b", "b");
    assert(ctr.getAll().size() == 2);
    ctr.updateMed("b",8 ,"c", "c");
    assert(ctr.getAll().size() == 2);
}

void testCautaCtr() {
    MedicamentRepo rep;
    MedValidator val;
    MedService ctr{ rep,val };
    ctr.addMed("a",6 ,"a", "a");
    ctr.addMed("b",6 ,"b", "b");
    assert(ctr.getAll().size() == 2);
    ctr.cautaMed("a");
    assert(ctr.getAll().size() == 2);
}

void testFiltrare() {
    MedicamentRepo rep;
    MedValidator val;
    MedService ctr{ rep,val };
    ctr.addMed("a",9 ,"a", "a");
    ctr.addMed("b",80 ,"b", "b");
    ctr.addMed("c",7 ,"c", "c");
    assert(ctr.filtrarePret(6).size() == 0);
    assert(ctr.filtrarePret(80).size() == 1);
    assert(ctr.filtrareSubstanta("a").size()==1);
}


void testSortare() {

    MedicamentRepo rep;
    MedValidator val;
    MedService serv{ rep,val };

    constexpr int pret = 1;
    string den = "iai";
    string prod = "pap";
    string nrI2 = "aaa";
    string subst = "mam";
    string den2= "aaa";
    

    serv.addMed(den, pret, prod, subst);
    serv.addMed(den2, pret, prod, subst);
    DynamicVector<Medicament>v = serv.sort([](const Medicament& m1, const Medicament& m2) {if (m1.getDenumire() < m2.getDenumire()) return true; else return false; });
    assert(v.size() == 2);
    v = serv.sort([](const Medicament& m1, const Medicament& m2) {if (m1.getProducator() < m2.getProducator()) return true; else return false; });
    assert(v.size() == 2);
    v = serv.sort([](const Medicament& m1, const Medicament& m2) {
        if (m1.getSubstanta() < m2.getSubstanta())return true;
        else if (m1.getSubstanta() == m2.getSubstanta())
            if (m1.getPret() < m2.getPret())return true;
            else return false;
        else return false;
    });
    assert(v.size() == 2);
}
void testCtr() {
    testAdaugaCtr();
    testStergeCtr();
    testModificaCtr();
    testCautaCtr();
    testFiltrare();
    testSortare();
}
