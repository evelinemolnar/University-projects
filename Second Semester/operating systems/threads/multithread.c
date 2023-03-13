#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int n, m; // n = numarul de operanzi; m = min {2^k >= n} 
int* a; // valoarea 1 pentru pana la n-1,  0 de la n la m-1
pthread_t *tid; // id-urile threadurilor; -1 thread nepornit
pthread_mutex_t print = PTHREAD_MUTEX_INITIALIZER; // Printare exclusiva

// Rutina thread-ului nr i de adunare
void* aduna(void* pi) {
    int i, j, sa, da, st = 0, dr = 0, k;
    i = *(int*)pi; // Retine numarul threadului
    if (i < m / 2) {
        st = 2 * i; // Retine fiul stang
        dr = st + 1; // Retine fiul drept
        while (tid[st] == -1);     // Asteapta sa inceapa fiul stang
        // while (tid[st] == -1) sleep(1); // poate asa!
        // Cel mai sanatos este să se utilizeze un set de variabile coditionale
        // care sa semnaleze pornirile threadurilor.
        while (tid[dr] == -1);     // Asteapta sa inceapa fiul drept
        // while (tid[dr] == -1) sleep(1); // poate asa!
        pthread_join(tid[st], NULL); // Asteapta sa se termine fiul stang
        pthread_join(tid[dr], NULL); // Asteapta sa se termine fiul drept
    }
    for (j = m; j > i; j /= 2); // Determina fratele cel mic
    for (k = j, sa = 0; k < i; k++) sa += m / j; // operand stang
    da = sa + m / j / 2; // operand drept
    a[sa] += a[da]; // Face adunarea proppriu-zisa
    pthread_mutex_lock(&print);// Asigura printare exclusiva
    printf("Thread %d: a[%d] += a[%d]", i, sa, da);
    if (st > 0) printf(" (dupa fii %d %d)\n", st, dr); else printf("\n");
    pthread_mutex_unlock(&print);
}

// Functia main, in care se creeaza si lanseaza thread-urile 
int main(int argc, char* argv[]) {
    n = atoi(argv[1]); // Numarul de numere de adunat
    for (m = 1; n > m; m *= 2); // m = min {2^k >= n}
    int* pi;
    int i;
    a = (int*) malloc(m*sizeof(int)); // Spatiu pentru intregii de adunat
    pi = (int*) malloc(m*sizeof(int)); // Spatiu pentru indicii threadurilor
    tid = (pthread_t*) malloc(m*sizeof(pthread_t)); // id-threads
    for (i = 0; i < n; i++) a[i] = 1; // Aduna numarul 1 de n ori
    for (i = n; i < m; i++) a[i] = 0; // Completeaza cu 0 pana la m
    for (i = 1; i < m; i++) tid[i] =-1; // Threadurile sunt inca nepornite
    for (i = 1; i < m; i++) pi[i] = i; // Threadurile sunt inca nepornite
    for (i = 1; i < m; i++) 
        // De ce folosim mai jos &pi[i] in loc de &i? vezi un exemplu precedent!
        pthread_create(&tid[i], NULL, aduna, (void*)(&pi[i])); // Threadul i 
    pthread_join(tid[1], NULL); // Asteapta dupa primul thread
    printf("Terminat adunarile pentru n = %d. Total: %d\n", n, a[0]);
    free(a); // Eliberaza tabloul de numere
    free(pi); // Elibereaza tabloul de indici de threaduri
    free(tid); // Elibereaza tabloul de id-uri de threaduri
}

