#include "mainwindow.h"
#include "GUI.h"
#include "FileRepository.h"
#include "guimodele.h"
#include <iostream>
#include <QtWidgets/QApplication>
#include <QApplication>

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

//void test_all();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //FileRepo repo{ "fileRepo.txt" };
    Repo repo;
    Validate val;
    Service serv{ repo, val };
    adaugaCateva(serv);
    //Console consola{ serv };

    PetStoreGUIModele gui{ serv };

    //test_all();
    //consola.run();
    gui.show();

    return a.exec();
}


