#include "Matrice.h"

#include <exception>

using namespace std;

//functioa care da hashCode-ul unuei element
int hashCode(TElem e){
//ptr moment numarul e intreg
    return abs(e);
}

int Matrice::dispersie(TElem key) const
{
    return abs(key % (this->m));
}


Matrice::Matrice(int m, int n) {
	/* de adaugat */
    tabela = new PNod[CAP];

    for (int i = 0; i < CAP; i++)
        tabela[i] = nullptr;

    m = 10;
    n=10;
}



int Matrice::nrLinii() const{
	/* de adaugat */
	return n;
}


int Matrice::nrColoane() const{
	/* de adaugat */
	return m;
}


TElem Matrice::element(int i, int j) const{
	/* de adaugat */
	return -1;
}



TElem Matrice::modifica(int i, int j, TElem e) {
	/* de adaugat */
	return -1;
}

IteratorMatrice iterator(int coloana) {

}


