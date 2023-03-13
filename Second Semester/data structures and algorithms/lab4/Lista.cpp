#include <exception>

#include "IteratorLP.h"
#include "Lista.h"

#include <iostream>

int Lista::new_nod(TElem value){
    if(first_free == -1)
        alloc(2*capacity);
    int poz = first_free;
    list.value[poz] = value;
    first_free = list.next[poz];
    list.next[poz] = -1;
    size++;

    return poz;
}

void Lista::alloc(int new_capacity){
    auto* new_next = new int[new_capacity];
    auto* new_prev = new int[new_capacity];
    auto* new_value = new TElem[new_capacity];

    for(int i = 0;i < capacity;i++){
        new_next[i] = list.next[i];
        //new_prev[i] = list.prev[i];
        new_value[i] = list.value[i];
    }
    first_free = capacity;
    for(int i = capacity; i <new_capacity-1; i++)
        new_next[i] = i + 1;
    new_next[new_capacity-1] = -1;
    capacity = new_capacity;
    delete[] list.next;
    delete[] list.value;
    //delete[] list.prev;
    list.next = new_next;
    list.value = new_value;
    //list.prev = new_prev;
}


Lista::Lista() {
    /* de adaugat */
    size = capacity = 0;
    first_free = 0;
    list.next = nullptr;
    list.value = nullptr;
    alloc(50);
    first = -1;
}

int Lista::dim() const {
    /* de adaugat */
    return size;
}


bool Lista::vida() const {
    /* de adaugat */
    return size == 0;
}

IteratorLP Lista::prim() const {
    /* de adaugat */
    return IteratorLP(*this);
}

TElem Lista::element(IteratorLP poz) const {
    /* de adaugat */
    if(!poz.valid())
        throw std::exception();
    return poz.element();
}

TElem Lista::sterge(IteratorLP& poz) {
    /* de adaugat */
    if(!poz.valid())
        throw std::exception();
    int current = first;
    if(current != poz.current)
        while(list.next[current] != poz.current){
            current = list.next[current];}
    int temp = poz.current;
    poz.urmator();
    list.next[current] = poz.current;
    size--;
    list.next[temp] = first_free;
    first_free = temp;
    return list.value[temp];
}

IteratorLP Lista::cauta(TElem e) const{
    /* de adaugat */
    int current = first;
    while(current != -1 && list.value[current] != e)
        current = list.next[current];
    auto it = IteratorLP(*this);
    if(current == -1)
        it.current = -1;
    else
        it.current = current;
    return it;
}

TElem Lista::modifica(IteratorLP poz, TElem e) {
    /* de adaugat */
    if(!poz.valid())
        throw std::exception();
    TElem temp = poz.element();
    list.value[poz.current] = e;
    return temp;
}

void Lista::adauga(IteratorLP& poz, TElem e) {
    /* de adaugat */
    if(!poz.valid())
        throw std::exception();
    int n = new_nod(e);
    int current = first;
    while(list.next[current] != poz.current)
        current = list.next[current];
    list.next[n] = list.next[poz.current];
    list.next[current] = n;
    poz.current = n;
}

void Lista::adaugaInceput(TElem e) {
    /* de adaugat */
    int poz = new_nod(e);
    list.next[poz] = first;
    first = poz;
}

void Lista::adaugaSfarsit(TElem e) {
    /* de adaugat */
    int poz = new_nod(e);
    if(first == -1)
        first = poz;
    else {
        int current = first;
        while (list.next[current] != -1)
            current = list.next[current];
        list.next[poz] = -1;
        list.next[current] = poz;
    }
}

Lista::~Lista() {
    /* de adaugat */
    delete[] list.next;
    delete[] list.value;
}
