#include "Service.h"
#include "Validation.h"
#include "FileRepository.h"
#include "Repository.h"
#include "UI.h"
#include <iostream>


void test_all();

void adaugaCateva(Service& ctr){
    ctr.adauga("Nurofen","MMM", "aa",100);
    ctr.adauga("Paracetamol","fff", "bb",10);
    ctr.adauga("Strepsils","MMM", "cc",50);
    ctr.adauga("a","MMM", "aa",20);
    ctr.adauga("b","fff", "bb",200);
    ctr.adauga("c","fff", "cc",150);
    ctr.adauga("d","MMM", "aa",100);
    ctr.adauga("e","fff", "bb",10);
    ctr.adauga("f","MMM", "cc",30);
    ctr.adauga("g","fff", "aa",70);
    ctr.adauga("h","MMM", "bb",80);
    ctr.adauga("i","fff", "cc",90);
    ctr.adauga("j","MMM", "aa",105);
    ctr.adauga("k","fff", "bb",40);
    ctr.adauga("z","MMM", "cc",10);

}

int main()
{
    FileRepo repo{ "../fileRepo.txt" };
    //Repo repo;
    Validate val;
    Service serv{ repo, val };
    Console consola{ serv };
    //adaugaCateva(serv);
    test_all();
    consola.run();
}
// 1.
void test_all()
{
    std::cout << "Start tests!\n";
    test_domain();
    test_repoExp();
    test_repo();
    test_add_service();
    test_sterge_service();
    test_modifica_service();
    test_find();
    test_filter_pret();
    test_filter_sub();
    test_sort();
    test_reteta();
    test_map();
    test_undo();
    cout << "Finish tests!\n";
}