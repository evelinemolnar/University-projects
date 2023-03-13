#include "FileRepository.h"
#include "Repository.h"
#include <assert.h>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

//filerepo
void FileRepo::readFromFile()
{
    ifstream in(filepath);
    string line, denumire, producator, substanta, pret;
    int id_int;

    while (getline(in, line))
    {
        istringstream stringInput(line);
        //stringInput >> id;
        getline(stringInput, denumire, ' ');
        getline(stringInput, producator, ' ');
        getline(stringInput, substanta, ' ');
        getline(stringInput, pret, ' ');
        id_int = stod(pret);
        Medicament toAdd{denumire,producator,substanta,static_cast<double>(id_int) };
        Repo::add(toAdd);
    }

    in.close();
}

void FileRepo::writeToFile()
{
    vector < Medicament > med = Repo::get_all();
    ofstream out(filepath);
    if (!out.is_open()) cout << "Unable to open file: " + filepath + "\n";
    for (const auto& m : med)
    {
        out << m.get_denumire() << " " << m.get_producator() << " " << m.get_substanta_activa() << " " << m.get_pret() <<"\n";
    }
    out.close();
}

FileRepo::FileRepo(std::string FileName) : Repo()
{
    filepath = FileName;
    readFromFile();
}

void FileRepo::store(const Medicament& m)
{
    Repo::add(m);
    writeToFile();
}
void FileRepo::del(const Medicament& m)
{
    Repo::delete_medicine(m);
    writeToFile();
}
void FileRepo::update(const Medicament& m)
{
    Repo::modify(m);
    writeToFile();
}

