#pragma once
#include "Repository.h"
#include <string>
#include <fstream>

class FileRepo : public Repo {
private:

    std::string filepath;
    void readFromFile();
    void writeToFile();

public:

    FileRepo(std::string FileName);

    void store(const Medicament& m) ;
    void del(const Medicament& m) ;
    void update(const Medicament& m) ;


};

