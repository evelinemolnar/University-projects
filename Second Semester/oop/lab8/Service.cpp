//
// Created by Eveline Molnar on 21.04.2022.
//


#include "Service.h"
#include <functional>
#include <algorithm>
#include <cassert>
#include <random>
#include <iterator>
using namespace std;


/*
vector<Medicament> MedService::generalSort(bool(*maiMicF)(const Medicament&, const Medicament&)) {
    vector<Medicament> v{ rep.getAll() };//fac o copie
    for (size_t i = 0; i < v.size(); i++) {
        for (size_t j = i + 1; j < v.size(); j++) {
            if (!maiMicF(v[i], v[j])) {Medicament aux = v[i];v[i] = v[j];v[j] =  aux;}
        }
    }
    return v;
}*/


void ServiceReteta::addReteta(const std::string& denumire) {
    std::vector < Medicament > medicamente = rep.FindMedsAfterName(denumire);
    if(medicamente.empty()){throw MedRepoException("Nu exista acest medicament");}
    ret.add(medicamente[0]);
}

void ServiceReteta::clearRetServ(){
    ret.clear();
}

int ServiceReteta::addRandom(int numberToAdd)
{
    int rndNr ;
    int cateAdaugate = 0;

    string prod;
    string den;
    string pret;
    string subst;

    while (cateAdaugate < numberToAdd) {

        std::mt19937 mt{ std::random_device{}() };
        int numarMed = (int)numar_medSRV();
        std::uniform_int_distribution<> dist(numarMed, numarMed + numberToAdd * 2);

        try {
            rndNr = dist(mt);
            den = "Denumire" + to_string(rndNr);

            prod = "Prod" + to_string(rndNr);
            subst = "Substanta activa." + to_string(rndNr);
            addMedRet(den,rndNr,prod, subst);
            cateAdaugate++;
        }
        catch (const exception&) {continue;}
    }
    return cateAdaugate;
}

void ServiceReteta::addMedRet(const string &denumire, int pret, const string &producator, const string &substanta) {
    Medicament p{ denumire, pret, producator, substanta };
    val.validate(p);
    ret.add(p);
}

size_t ServiceReteta::numar_medSRV() {
    return ret.numar_med();
}

const std::vector<Medicament>& ServiceReteta::srv_getReteta() const {
    return ret.getReteta();
}

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
    val.validate(p);
    rep.update(p);
}

void MedService::cautaMed(const string &denumire)  {
    rep.find(denumire);
}
/*
vector<Medicament> MedService::sort(function<bool(const Medicament& m1, const Medicament& m2)>compareFunction) const
{
    vector<Medicament>v = rep.getAll();
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
*/
vector<Medicament> MedService::sortByDenumire() {
    auto copyAll = rep.getAll();
    std::sort(copyAll.begin(), copyAll.end(), cmpDenumire);
    return copyAll;
    //return generalSort(cmpType);
}


vector<Medicament> MedService::sortByProducator() {
    auto copyAll = rep.getAll();
    std::sort(copyAll.begin(), copyAll.end(), cmpProducator);
    return copyAll;
}
/*
vector<Medicament> MedService::sortBySubstPret() {
    return generalSort([](const Medicament&p1, const Medicament&p2) {
        if (p1.getSubstanta() == p2.getSubstanta()) return p1.getPret() < p2.getPret();
        return p1.getSubstanta() < p2.getSubstanta();
    });
}
*/

vector<Medicament> MedService::filtrarePret(int pretMin, int pretMax) {
    return filtreaza([=](const Medicament& p) {
        return p.getPret() >= pretMin && p.getPret() <= pretMax;
    });
}

vector<Medicament> MedService::filtrareSubstanta(const string &subst)  {
    return filtreaza([subst](const Medicament& m) {
        return m.getSubstanta() == subst;
    });
}

vector<Medicament> MedService::filtreaza(function<bool(const Medicament&)> fct){
    vector<Medicament> rez;
    vector<Medicament> v1;
    v1 = rep.getAll();
    for (const auto& Med : v1) {
        if (fct(Med)) {
            rez.push_back(Med);
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
    assert(ctr.filtrarePret(6, 70).size() == 2);
    assert(ctr.filtrarePret(6, 90).size() == 3);
    assert(ctr.filtrareSubstanta("a").size()==1);
}


void testSortare() {
    MedicamentRepo rep;
    MedValidator val;
    MedService ctr{ rep,val };

    ctr.addMed("a",9 ,"b", "a");
    ctr.addMed("b",8 ,"a", "b");
    ctr.addMed("c",7 ,"c", "c");

    auto firstP = ctr.sortByDenumire()[0];
    assert(firstP.getDenumire() == "a");

    firstP = ctr.sortByProducator()[0];
    assert(firstP.getProducator() == "a");

    //firstP = ctr.sortBySubstPret()[0];
    //assert(firstP.getPret() == 9);
    Medicament m1("a",20,"a","a" );
    Medicament m2("b",20,"a","a" );
    //firstP = ctr.sort(m1,m2);


}

void testRetetaServ()
{
    MedicamentRepo repo;
    MedValidator valid;
    Reteta ret;
    ServiceReteta serv(repo, ret, valid);
    Medicament med1("a",20,"a","a" );
    Medicament med2("b",20,"a","a" );
    Medicament med3("c",20,"a","a" );
    Medicament med4("d",20,"a","a" );
    std::vector < Medicament > meds;

    repo.store(med1);
    repo.store(med2);
    repo.store(med3);
    repo.store(med4);

    serv.addReteta("a");
    serv.addReteta("b");
    serv.addReteta("c");

    meds = serv.srv_getReteta();
    assert(meds.size() == 3);

    serv.clearRetServ();
    meds = serv.srv_getReteta();
    assert(meds.size() == 0);

    serv.addRandom(10);
    meds = serv.srv_getReteta();
    assert(meds.size() > 1);
}

void testCtr() {
    testAdaugaCtr();
    testStergeCtr();
    testModificaCtr();
    testCautaCtr();
    testFiltrare();
    testSortare();
    testRetetaServ();
}
