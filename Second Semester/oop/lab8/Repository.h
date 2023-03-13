//
// Created by Eveline Molnar on 21.04.2022.
//

#pragma once
#include "Medicament.h"
#include <utility>
#include <vector>
#include <string>
#include <ostream>

using std::vector;
using std::string;
using std::ostream;

class MedicamentRepo {
    friend class ServiceReteta;
    vector<Medicament> all;
    /*
    metoda privata verifica daca exista deja m in repository
    */
    bool exist(const Medicament& m) const;
public:
    MedicamentRepo() = default;
    //nu permitem copierea de obiecte
    MedicamentRepo(const MedicamentRepo& ot) = delete;
    /*
    Salvare med
    arunca exceptie daca mai exista un medicament cu aceeasi denumire
    */
    void store(const Medicament& m);

    void del(const string& denumire);

    void update(const Medicament& med);
    /*
    Cauta
    arunca exceptie daca nu exista med
    */
    const Medicament& find(const string& denumire) const;

    /*
    returneaza toate medicamentele salvate
    */
    const vector<Medicament>& getAll() const noexcept;

    std::vector < Medicament > FindMedsAfterName(const std::string& Name);

};

class Reteta
{
private:
    std::vector<Medicament> MemoryReteta;
public:
    Reteta()= default;
    void add(Medicament&);
    void clear();
    const std::vector<Medicament>& getReteta() const;
    size_t numar_med() const;
};


/*
Folosit pentru a semnala situatii exceptionale care pot aparea in repo
*/
class MedRepoException {
    string msg;
public:
    explicit MedRepoException(string m) :msg{std::move( m )} {}
    //functie friend (vreau sa folosesc membru privat msg)
    friend ostream& operator<<(ostream& out, const MedRepoException& ex);
};

ostream& operator<<(ostream& out, const MedRepoException& ex);

void testeRepo();