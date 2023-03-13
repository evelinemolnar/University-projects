#include "Iterator.h"
#include "DO.h"
#include <exception>
using namespace std;

Iterator::Iterator(const DO& d) : dict(d){
	/* de adaugat */
    current = dict.start;
}

void Iterator::prim(){
	/* de adaugat */
    current = dict.start;
}

void Iterator::urmator(){
	/* de adaugat */
    if(!this->valid())
        throw exception();
    current = current->next;
}

bool Iterator::valid() const{
	/* de adaugat */
    if(current == nullptr)
        return false;
    return true;
}

TElem Iterator::element() const{
	/* de adaugat */
    if(!this->valid())
        throw exception();
    return pair <TCheie, TValoare>  (current->element.first, current->element.second);
}


