//
// Created by Eveline Molnar on 21.04.2022.
//
#include "Repository.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <algorithm>

using std::ostream;
using std::stringstream;

size_t Reteta::numar_med() const {
    std::vector<Medicament> medicamente;
    medicamente =getReteta();
    return medicamente.size();
}


void MedicamentRepo::store(const Medicament& m)
{
    if (exist(m)) {
        throw MedRepoException("Exista acest medicament.");
    }
    all.push_back(m);
}

bool MedicamentRepo::exist(const Medicament& m) const{
    try {
        find(m.getDenumire());
        return true;
    }
    catch (MedRepoException&) {
        return false;
    }
}

void MedicamentRepo::del(const string& denumire)
{
    auto it = find_if(all.begin(), all.end(), [=](const Medicament& ma) {return ma.getDenumire() == denumire; });

    if (it != all.end()) {
        all.erase(it);
    }
    else {
        throw MedRepoException("Nu exista acest medicament.");
    }
}


void MedicamentRepo::update(const Medicament& m)
{
    auto it = find_if(all.begin(), all.end(), [=](const Medicament& ma) {return ma.getDenumire() == m.getDenumire(); });
    
    if (it != all.end()) {
        *it = m;
    }
    else {
        throw MedRepoException("Nu exista aceast medicament.");
    }
}

/*
Cauta
arunca exceptie daca nu exista
*/
const Medicament& MedicamentRepo::find(const string& denumire) const{
    for (const auto& m : all) {
        if (m.getDenumire()==denumire) {
            return m;
        }
    }
    //daca nu exista arunc o exceptie
    throw MedRepoException("Exista acest medicament.");
}

/*
returneaza toate med salvate
*/
const vector<Medicament>& MedicamentRepo::getAll() const noexcept {
    return all;
}


ostream& operator<<(ostream& out, const MedRepoException& ex) {
    out << ex.msg;
    return out;
}

std::vector < Medicament > MedicamentRepo::FindMedsAfterName(const std::string& Name)
{
    std::vector < Medicament > toReturn;
    for (auto& iterator : all)
    {
        if (iterator.getDenumire() == Name)
        {
            toReturn.push_back(iterator);
        }
    }
    return toReturn;
}

void Reteta::add(Medicament& ToAdd)
{
    MemoryReteta.push_back(ToAdd);
}

void Reteta::clear()
{
    MemoryReteta.clear();
}

const std::vector < Medicament >& Reteta::getReteta() const
{
    return MemoryReteta;
}


void testAdauga() {
    MedicamentRepo rep;
    rep.store(Medicament{"a", 12, "z", "z"});
    assert(rep.getAll().size() == 1);
    assert(rep.find("a").getDenumire() == "a");

    rep.store(Medicament{"b", 12, "b", "b"});
    assert(rep.getAll().size() == 2);

    try {
        rep.store(Medicament{"a", 12, "z", "z"});
        assert(false);
    }
    catch (const MedRepoException &) {
        assert(true);
    }
    //cauta inexistent
    try {
        rep.find("c");
        assert(false);
    }
    catch (const MedRepoException &e) {
        stringstream os;
        os << e;
        assert(os.str().find("exista") >= 0);
    }
}

void testSterge() {
    MedicamentRepo rep;
    rep.store(Medicament{ "a",20,"a","a" });
    rep.store(Medicament{ "b",30,"b","b" });
    assert(rep.getAll().size() == 2);
    rep.del("a");
    assert(rep.getAll().size() == 1);
    //cauta inexistent
    try {
        rep.del("a");
        assert(false);
    }
    catch (const MedRepoException& e) {
        stringstream os;
        os << e;
        assert(os.str().find("exista") >= 0);
    }
}

void testModifica() {
    MedicamentRepo rep;
    rep.store(Medicament{ "a",20,"a","a" });
    rep.store(Medicament{ "b",30,"b","b" });
    assert(rep.getAll().size() == 2);
    rep.update(Medicament{ "b",40,"c","c" });
    assert(rep.getAll().size() == 2);
    auto m = rep.find("b");
    assert(m.getPret() == 40);
    assert(m.getProducator() == "c");
    assert(m.getSubstanta() == "c");
    try {
        rep.update(Medicament{ "z",50,"z","z" });
        assert(false);
    }
    catch (const MedRepoException& e) {
        stringstream os;
        os << e;
        assert(os.str().find("exista") >= 0);
    }
}

void testCauta() {
    MedicamentRepo rep;
    rep.store(Medicament{ "a",12,"a","a" });
    rep.store(Medicament{ "b",12,"b","b" });

    auto p = rep.find("a");
    assert(p.getDenumire() == "a");
    assert(p.getProducator() == "a");

}

void testRetetaRepo()
{
    MedicamentRepo repo;
    Reteta ret;
    Medicament med1("a",20,"a","a" );
    Medicament med2("b",20,"a","a" );
    Medicament med3("c",20,"a","a" );
    Medicament med4("d",20,"a","a" );
    std::vector < Medicament > meds;

    repo.store(med1);
    repo.store(med2);
    repo.store(med3);
    repo.store(med4);

    ret.add(med1);
    ret.add(med2);
    ret.add(med3);

    meds = ret.getReteta();
    assert(meds.size() == 3);

    ret.clear();
    meds = ret.getReteta();
    assert(meds.empty());

}




void testeRepo() {
    testAdauga();
    testCauta();
    testModifica();
    testSterge();
    testRetetaRepo();
}
