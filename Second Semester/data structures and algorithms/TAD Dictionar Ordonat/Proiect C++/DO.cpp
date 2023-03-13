#include "Iterator.h"
#include "DO.h"
#include <iostream>

#include <exception>
using namespace std;

DO::DO(Relatie r) {
    /* de adaugat */
    order = r;
    start = nullptr;
}

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
TValoare DO::adauga(TCheie c, TValoare v) {
    /* de adaugat */

    node* previous = nullptr;
    node* current = start;
    while(current != nullptr){
        if(c == current->element.first){
            TValoare temp = current->element.second;
            current->element.second = v;
            return temp;
        }
        if(!order(current->element.first, c)){
            break;
        }
        previous = current;
        current = current->next;
    }
    auto *element = new node(c , v , nullptr, nullptr);

    if(previous == nullptr){
        element->next = start;
        start = element;
    }
    else{
        previous->next = element;
        element->next = current;
    }
    return NULL_TVALOARE;
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) const {
    /* de adaugat */
    auto i = iterator();
    while(i.valid() && order(i.element().first, c)){
        if(i.element().first == c)
            return i.element().second;
        i.urmator();
    }
    return NULL_TVALOARE;
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
TValoare DO::sterge(TCheie c) {
    /* de adaugat */

    node* previous = nullptr;
    auto current = start;

    while(current != nullptr && current->element.first != c){
        previous = current;
        current = current->next;
    }

    if(current == nullptr){
        return NULL_TVALOARE;
    }

    if(previous == nullptr)
        start = current->next;
    else
        previous->next = current->next;

    TValoare temp = current->element.second;
    free(current);

    return temp;
}


//returneaza numarul de perechi (cheie, valoare) din dictionar
int DO::dim() const {
    /* de adaugat */
    //teta(n)
    auto i = start;
    int size = 0;
    while(i!= nullptr){
        size++;
        i = i->next;
    }
    return size;
}

//verifica daca dictionarul e vid
bool DO::vid() const {
    /* de adaugat */
    //o(1)
    if(start == nullptr)
        return true;
    return false;
}

Iterator DO::iterator() const {
    return  Iterator(*this);
}

DO::~DO() {
    /* de adaugat */
    //O(1)
    node* ptr = start;
    node* temp;
    while(ptr != nullptr)
    {
        temp = ptr->next;
        free(ptr);
        ptr = temp;
    }
}

void filtreaza(Condiție cond){
 //complexitate BC
 //WC
 //AC
    auto i = iterator();
    while(i.valid() && order(i.element().first, c)){
        if(i.element().first == c)
            return i.element().second;
        i.urmator();
    }
}