#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXLINIE 1000
pthread_t tid[100];
// pthread_t tid; // Vezi comentariul de la sfârşitul sursei
void* ucap(void* numei) {
    printf("Threadul: %ld ...> %s\n", pthread_self(), (char*)numei);
    FILE *fi, *fo;
    char linie[MAXLINIE], numeo[100], *p;
    strcpy(numeo, (char*)numei);
    strcat(numeo, ".CAPIT");
    fi = fopen((char*)numei, "r");
    fo = fopen(numeo, "w");
    for ( ; ; ) {
        p = fgets(linie, MAXLINIE, fi);
        linie[MAXLINIE-1] = '\0';
        if (p == NULL) break;
        if (strlen(linie) == 0) continue;
        linie[0] = toupper(linie[0]); // Cuvant incepe in coloana 0 
        for (p = linie; ; ) {
            p = strstr(p, " ");
            if (p == NULL) break;
            p++;
            if (*p == '\n') break;
            *p = toupper(*p);
        }
        fprintf(fo, "%s", linie);
    }
    fclose(fo);
    fclose(fi);
    printf("Terminat threadul: %ld ...> %s\n", pthread_self(), (char*)numei);
}
int main(int argc, char* argv[]) {
    int i;
    for (i=1; argv[i]; i++) {
        pthread_create(&tid[i], NULL, ucap, (void*)argv[i]);
        // pthread_create(&tid, NULL, ucap, (void*)argv[i]); // Vezi comentariul de la sfârşitul sursei
        printf("Creat threadul: %ld ...> %s\n", tid[i], argv[i]);
    }
    for (i=1; argv[i]; i++) pthread_join(tid[i], NULL);
    // for (i=1; argv[i]; i++) pthread_join(tid, NULL); // Vezi comentariul de la sfârşitul sursei
    printf("Terminat toate threadurile\n");
}

