#pragma once

typedef int TElem;

class IteratorLP;

class Lista {
private:
    friend class IteratorLP;
    /* aici e reprezentarea */
    int capacity;
    int first;
    int last;
    int first_free;
    int size;
    struct {
        int *next;
        int *prev;
        TElem *value;
    }list;
private:
    //Teta(new_capacity)
    void alloc(int new_capacity);

    //Teta(1)
    int new_nod(TElem value);
public:

    // constructor   //Teta(1)
    Lista ();

    // returnare dimensiune    //Teta(1)
    int dim() const;

    // verifica daca lista e vida   //Teta(1)
    bool vida() const;

    // prima pozitie din lista    //Teta(1)
    IteratorLP prim() const;

    // returnare element de pe pozitia curenta
    //arunca exceptie daca poz nu e valid      //Teta(1)
    TElem element(IteratorLP poz) const;

    // modifica element de pe pozitia poz si returneaza vechea valoare
    //arunca exceptie daca poz nu e valid     //Teta(1)
    TElem modifica(IteratorLP poz, TElem e);

    // adaugare element la inceput     //Teta(1)
    void adaugaInceput(TElem e);

    // adaugare element la sfarsit     //Teta(capacitate)
    void adaugaSfarsit(TElem e);

    // adaugare element dupa o pozitie poz
    //dupa adaugare poz este pozitionat pe elementul adaugat
    //arunca exceptie daca poz nu e valid    //O(capacity)
    void adauga(IteratorLP& poz, TElem e);

    // sterge element de pe o pozitie poz si returneaza elementul sters
    //dupa stergere poz este pozitionat pe elementul de dupa cel sters
    //arunca exceptia daca poz nu e valid     //O(capacity)
    TElem sterge(IteratorLP& poz);

    // cauta element si returneaza prima pozitie pe care apare (sau iterator invalid)
    //O(capacity)
    IteratorLP cauta(TElem e) const;

    //destructor
    //Teta(1)
    ~Lista();
};
