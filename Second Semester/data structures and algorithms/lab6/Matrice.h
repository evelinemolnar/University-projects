#pragma once

typedef int TElem;

#define NULL_TELEMENT 0
#define CAP 10
class Nod;

typedef std::pair <int, int> linCol;
typedef std::pair <linCol, int> TValue;

typedef Nod* PNod;

class Nod
{
private:
    //TipElem element;
    Nod* urm;
    Nod* ant;
public:
    //Nod(TipElem, Nod*, Nod*);
    friend class Matrice;
    friend class Matrice;
};

class IteratorMatrice
{
private:
    int col;
public:
    friend class Matrice;
};


class Matrice {

    friend class IteratorMatrice;
private:
	/* aici e reprezentarea */
    int m;
    int n;
    int val;
    PNod* tabela;
    int dispersie(TElem) const;
    int size=0;

public:

	//constructor
	//se arunca exceptie daca nrLinii<=0 sau nrColoane<=0
	Matrice(int nrLinii, int nrColoane);


	//destructor
	~Matrice(){};

    void adauga(TElem e);

    bool sterge(TElem e);

	//returnare element de pe o linie si o coloana
	//se arunca exceptie daca (i,j) nu e pozitie valida in Matrice
	//indicii se considera incepand de la 0
	TElem element(int i, int j) const;


	// returnare numar linii
	int nrLinii() const;

	// returnare numar coloane
	int nrColoane() const;


	// modificare element de pe o linie si o coloana si returnarea vechii valori
	// se arunca exceptie daca (i,j) nu e o pozitie valida in Matrice
	TElem modifica(int i, int j, TElem);

    //TAD Matrice

// creaza un iterator asupra tuturor elementelor matricei pe o anumită coloană (indiferent dacă acestea sunt sau nu NULL_TELEM).

// aruncă excepție în cazul în care coloana nu este o coloană validă

    IteratorMatrice iterator(int coloana) const;

    //Obs:  Va trebui implementată clasa IteratorMatrice, de as

};







