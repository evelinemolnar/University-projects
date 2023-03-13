/*
#include "abstractrepo.h"

size_t RepoMedicamente::getSize(){
    return this->RepoMed.size();
}

unordered_map <string, Medicament>& RepoMedicamente::getAll(){
    return RepoMed;
}

vector<Medicament>& RepoMedicamente::getRec(){
    return Reteta;
}

void RepoMedicamente::addMedicament(const Medicament& m){
    for(auto& med : RepoMed)
        if(med.second == m){
            throw (Exception("Medicament deja existent!\n"));
        }
    this->RepoMed.insert(m.get_denumire(), m);
}

void RepoMedicamente::deleteMedicament(const string& nume, Medicament& medicament){
    int ok = 0, i = -1;
    for(auto& med : RepoMed){
        i++;
        if(med.second.get_denumire() == nume){
            medicament = med.second;
            //RepoMed.erase(med.second.get_denumire());
            ok = 1;
            break;
        }
    }
    if(!ok)
        throw (Exception("Medicament inexistent!\n"));
}

void RepoMedicamente::modifyMedicament(const Medicament& m, Medicament& medicament){
    int ok = 0, i = -1;
    for(auto& med : RepoMed){
        i++;
        if(med.second.get_denumire() == m.get_denumire()){
            ok = 1;
            medicament = med.second;
            //RepoMed.at(med.second.get_denumire()) = m;
            break;
        }
    }
    if(!ok)
        throw (Exception("Medicament inexistent!\n"));
}

void RepoMedicamente::addMedRec(const string& nume){
    int ok = 0;
    for(auto& med : RepoMed)
        if(med.second.get_denumire() == nume){
            ok = 1;
            Reteta.push_back(med.second);
            break;
        }
    if(!ok)
        throw (Exception("Medicament inexistent!\n"));
}

void RepoMedicamente::delRec(){
    Reteta.clear();
}
/*
void RepoMedicamente::rand(int nr) {
    if (RepoMed.size() == 0)
        throw ((Exception) ("Nu exista medicamente de adaugat in reteta!\n"));
    std::mt19937 mt{std::random_device{}()};
    std::uniform_int_distribution<> dist(0, int(RepoMed.size()) - 1);

    for (int i = 0; i < nr; i++) {
        int val = dist(mt);
        Reteta.push_back(RepoMed[val]);
    }
}*/
