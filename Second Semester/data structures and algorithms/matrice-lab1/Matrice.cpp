#include "Matrice.h"
#include <exception>
using namespace std;


Matrice::Matrice(int n, int m) {
    /* de adaugat */
    //complexitate generala: teta(1)
    if (n <= 0 || m <= 0) throw exception();
    this->m = m;
    this->n = n;
    cap = n * m;
    lung = 0;
    vector = new TPereche[cap];
}

Matrice::~Matrice() {
    //destructor
    //complexitate teta(1)
    delete vector;
}

int Matrice::nrLinii() const {
    //complexitate teta(1)
    return n;
}


int Matrice::nrColoane() const {
    //complexitate teta(1)
    return m;
}


TElem Matrice::element(int i, int j) const {
    //complexitate teta(log2(n))
    if (i < 0 || j < 0 || i >= n || j >= m) throw exception();
    int mij, st = 0, dr = lung - 1, pi, pj;
    while (st <= dr)
    {
        mij = (st + dr) / 2;
        pi = vector[mij].i;
        pj = vector[mij].j;
        if (pi == i && pj == j) return vector[mij].e;
        if (i < pi || i == pi && j < pj) dr = mij - 1;
        else st = mij + 1;
    }
    return NULL_TELEMENT;
}


TElem Matrice::modifica(int i, int j, TElem elem)
{   //complexitate teta(log2(n))
    if (i < 0 || j < 0 || i >= n || j >= m) throw exception();
    TElem old = element(i, j);
    int pi, pj, mij, st = 0 , dr = lung, lastst = 0;

    while (st < dr)
    {
        mij = (st + dr) / 2;
        pi = vector[mij].i;
        pj = vector[mij].j;
        if (pi == i && pj == j) { vector[mij].e = elem; return old; }
        if (pi == i && pj == j && vector[mij].e == NULL_TELEMENT) { vector[mij].e = elem; return NULL_TELEMENT; }
        if (pi == i && pj == j && elem == NULL_TELEMENT) {vector[mij].e = elem; return old;}
        if (i < pi || i == pi && j < pj)  dr = mij;
        else st = mij + 1 , lastst = st;
    }

    TPereche nou = { i,j,elem };
    int poz = lastst;
    if (elem!=0) {
        for (int q = lung - 1; q >= poz; q--)
            vector[q + 1] = vector[q];
        vector[poz] = nou;
        lung++;
    }




    return NULL_TELEMENT;

}