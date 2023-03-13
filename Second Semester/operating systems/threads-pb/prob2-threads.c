//scrieti unn program c care primeste oricate arg la linia de comanda(numere intregi)
//prog prinicipal are o functie int f[10], care reprez un vector de frecventa
// pt fiecare argument programul creeaza un thread care calculeaza frecventa , la final in main se  //face vect cu frecventa tuturor
#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h>

int f[10];
int v[10];
pthread_mutex_t m;

void* f(void* a){



}



int main(int argc, char** argv) {
    int i, n = 10;
    pthread_t t[10];

    if(argc > 1) {
        sscanf(argv[1], "%d", &n);
}



}





