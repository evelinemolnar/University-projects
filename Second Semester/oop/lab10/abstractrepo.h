
#pragma once
#include "Medicament.h"
#include <unordered_map>
#include <random>
#include <vector>
using namespace std;


class RepoMedicamente{
public:
    virtual size_t getSize();
    virtual unordered_map <string, Medicament>& getAll();
    virtual vector <Medicament>& getRec();
    virtual void addMedicament(const Medicament& m);
    virtual void deleteMedicament(const string& nume, Medicament& medicament);
    virtual void modifyMedicament(const Medicament& m, Medicament& medicament);
    virtual void addMedRec(const string& nume);
    virtual void delRec();
    virtual void rand(int nr);
    virtual ~RepoMedicamente() = default;
protected:
    unordered_map <string, Medicament> RepoMed;
    vector <Medicament> Reteta;
};

class Exception{

public:
    Exception(const string& msg): msg_(msg) {}
    ~Exception() {}

    string getMessage() const { return(msg_); }
private:
    string msg_;
};

class NewRepo: public RepoMedicamente{
private:
    int random;
public:
    int getRandom(){
        std::mt19937 mt{std::random_device{}()};
        std::uniform_int_distribution<> dist(0, 1);
        this->random = dist(mt);
        return random;
    }
    size_t getSize() override{
        if(getRandom() == 0)
            throw Exception("Error!\n");
        return RepoMedicamente::getSize();
    }
    unordered_map <string, Medicament>& getAll() override{
        if(getRandom() == 0)
            throw Exception("Error!\n");
        return RepoMedicamente::getAll();
    }
    vector <Medicament>& getRec() override{
        if(getRandom() == 0)
            throw Exception("Error!\n");
        return RepoMedicamente::getRec();
    }
    void addMedicament(const Medicament& m) override{
        if(getRandom() == 0)
            throw Exception("Error!\n");
        RepoMedicamente::addMedicament(m);
    }
    void deleteMedicament(const string& nume, Medicament& medicament) override{
        if(getRandom() == 0)
            throw Exception("Error!\n");
        RepoMedicamente::deleteMedicament(nume, medicament);
    }
    void modifyMedicament(const Medicament& m, Medicament& medicament) override{
        if(getRandom() == 0)
            throw Exception("Error!\n");
        RepoMedicamente::modifyMedicament(m, medicament);
    }
    void addMedRec(const string& nume) override{
        if(getRandom() == 0)
            throw Exception("Error!\n");
        RepoMedicamente::addMedRec(nume);
    }
    void delRec() override{
        if(getRandom() == 0)
            throw Exception("Error!\n");
        RepoMedicamente::delRec();
    }
    void rand(int nr) override{
        if(getRandom() == 0)
            throw Exception("Error!\n");
        RepoMedicamente::rand(nr);
    }
};