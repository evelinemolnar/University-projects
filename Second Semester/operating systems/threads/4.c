/*
Scrieti un program C care converteste toate literele mici din argumentele primite la linia de comanda in litere mari si afiseaza rezultatul. Folositi un thread pentru fiecare argument. 
*/
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct {
    int id;
    char str[100];
} argument;

void *upcase(void *arg) {
    int i;
    argument a = *((argument*)arg);
    for(i = 0; i < strlen(a.str); i++) {
        if(a.str[i] >= 'a' && a.str[i] <= 'z') {
            a.str[i] += 'A' - 'a';
        }
    }
    printf("Thread %d finished: %s\n", a.id, a.str);
    return NULL;
}

int main(int argc, char *argv[]) {
    int i;
    pthread_t *thrds = malloc(argc * sizeof(pthread_t));
    argument *args = malloc(argc * sizeof(argument));
    for(i = 0; i < argc; i++) {
	args[i].id = i;
        strcpy(args[i].str, argv[i]);
        if(0 > pthread_create(&thrds[i], NULL, upcase, (void*)&args[i])) {
            perror("Error on create thread");
        }
    }
    for(i = 0; i < argc; i++) {
	pthread_join(thrds[i], NULL);
    }
    free(thrds);
    free(args);
    return 0;
}

