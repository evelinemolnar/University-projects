#include "Repository.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <algorithm>

using std::ostream;
using std::stringstream;


void MedicamentRepo::store(const Medicament& m)
{
    if (exist(m)) {
        throw MedRepoException("Exista acest medicament.");
    }
    this->lista.add(m);
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

void MedicamentRepo::del(string denumire)
{
    auto it = lista.begin();
    while (it != lista.end() && denumire != (*it).getDenumire()) {
        ++it;
    }
    if (it != lista.end()) {
        lista.erase(it);
    }
    else {
        throw MedRepoException("Nu exista acest medicament.");
    }
}


void MedicamentRepo::update(const Medicament& m)
{
    auto it = lista.begin();
    while (it != lista.end() && m.getDenumire() != (*it).getDenumire()) {
        ++it;
    }
    if (it != lista.end()) {
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
const Medicament& MedicamentRepo::find(string denumire) const{
    for (int i = 0; i < lista.size(); i++)
        if (lista[i].getDenumire() == denumire)
            return lista[i];
    //daca nu exista arunc o exceptie
    throw MedRepoException("Exista acest medicament.");
}

/*
returneaza toate med salvate
*/
const DynamicVector<Medicament>& MedicamentRepo::getAll() const noexcept{
    return lista;
}


ostream& operator<<(ostream& out, const MedRepoException& ex) {
    out << ex.msg;
    return out;
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

void testeRepo() {
    testAdauga();
    testCauta();
    testModifica();
    testSterge();
}
