#include "Medicament.h"
bool cmpDenumire(const Medicament& p1, const Medicament& p2){
    return p1.getDenumire() < p2.getDenumire();
}


bool cmpProducator(const Medicament& p1, const Medicament& p2){
    return p1.getProducator() < p2.getProducator();
}