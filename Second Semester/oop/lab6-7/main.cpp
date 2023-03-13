#include "Console.h"
#include "Service.h"
#include "Repository.h"
#include "Validator.h"

void adaugaCateva(MedService& ctr){
    ctr.addMed("Nurofen", 25,  "MMM", "aa");
    ctr.addMed("Paracetamol", 10,  "FFF", "dd");
    ctr.addMed("Strepsils", 50,  "SSS", "bb");
    ctr.addMed("AAA", 100,  "MMM", "aa");
    ctr.addMed("BBB", 250,  "SSS", "bb");
    ctr.addMed("CCC", 15,  "FFF", "cc");
}

/*
template <typename MyVector>
MyVector testCopyIterate(MyVector v) {
    int totalP = 0;
    for (auto el : v) {
        totalP += el.getPret();
    }
    Masina m{ "total",totalP,"t","tttt"};
    v.add(m);
    return v;
}

template <typename MyVector>
void addMeds(MyVector& v, int cate) {
    for (int i = 0; i < cate; i++) {
        Masina m{i, std::to_string(i) + "_numar",std::to_string(i) + "_producator",std::to_string(i) + "_model", std::to_string(i) + "_tip" };
        v.add(m);
    }
}


Testare constructori / assignment
E template pentru a refolosi la diferite variante de VectorDinamic din proiect

template <typename MyVector>
void testCreateCopyAssign() {
    MyVector v;//default constructor
    addCars(v, 100);
    assert(v.size() == 100);
    assert(v[50].getDenumire() == "50_denumire");

    MyVector v2{ v };//constructor de copiere
    assert(v2.size() == 100);
    assert(v2[50].getTip() == "50_tip");

    MyVector v3;//default constructor
    v3 = v;//operator=   assignment
    assert(v3.size() == 100);
    assert(v3[50].getTip() == "50_tip");

    auto v4 = testCopyIterate(v3);
    assert(v4.size() == 101);
    assert(v4[50].getTip() == "50_tip");
}


  Test pentru move constructor si move assgnment

template <typename MyVector>
void testMoveConstrAssgnment() {
    std::vector<MyVector> v;
    //adaugam un vector care este o variabila temporara
    //se v-a apela move constructor
    v.push_back(MyVector{});

    //inseram, la fel se apeleaza move costructor de la vectorul nostru
    v.insert(v.begin(), MyVector{});

    assert(v.size() == 2);

    MyVector v2;
    addCars(v2, 50);

    v2 = MyVector{};//move assignment

    assert(v2.size() == 0);

}*/
/*
template <typename MyVector>
void testAll2() {
    testCreateCopyAssign<MyVector>();
    testMoveConstrAssgnment<MyVector>();
}*/

void testAll() {
    testeRepo();
    testCtr();
    testValidator();
}

int main() {
    testAll();
    //testAll2<DynamicVector<Medicament>>();
    MedicamentRepo rep;
    MedValidator val;
    MedService ctr{ rep,val };
    adaugaCateva(ctr);//adaug cateva el
    ConsolUI ui{ ctr };
    ui.start();
}
