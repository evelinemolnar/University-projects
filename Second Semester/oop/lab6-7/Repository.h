#pragma once
#include "Medicament.h"
#include "DynamicVector.h"
#include <vector>
#include <string>
#include <ostream>

using std::vector;
using std::string;
using std::ostream;

class MedicamentRepo {
    DynamicVector<Medicament>lista;
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

    void del(string denumire);

    void update(const Medicament& med);
    /*
    Cauta
    arunca exceptie daca nu exista med
    */
    const Medicament& find(string denumire) const;

    /*
    returneaza toate medicamentele salvate
    */
    const DynamicVector<Medicament>& getAll() const noexcept;

};

/*
Folosit pentru a semnala situatii exceptionale care pot aparea in repo
*/
class MedRepoException {
    string msg;
public:
    MedRepoException(string m) :msg{ m } {}
    //functie friend (vreau sa folosesc membru privat msg)
    friend ostream& operator<<(ostream& out, const MedRepoException& ex);
};

ostream& operator<<(ostream& out, const MedRepoException& ex);

void testeRepo();