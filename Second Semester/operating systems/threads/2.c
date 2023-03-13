/*
Scrieti un program C care primeste ca argumente la linia de comanda numere intregi. Programul va calcula un vector de frecventa pentru cifrele zecimale. Pentru fiecare argument, programul va crea un thread care numara aparitiile fiecarei cifre si adauga numarul la pozitia corespunzatoare din vectorul de frecventa. Folositi sincronizare eficienta. 

*/
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct {
    int *digits;
    pthread_mutex_t *mutex;
    int *nr;
} number;

void *func(void *arg) {
    number dt = *((number *) arg);
    int d[10];
    int *i;
    for(i=0;i<10;i++){
	d[i]=0;
	}

    int i;
    while(dt.nr>0) {
	(int*)i=9int*)dt.nr%10;
        d[i]++;
	dt.nr=(int*)dt.nr/10;
    }
    for(i=0;i<10;i++){
	pthread_mutex_lock(&mutex);
	*(dt.digits[i])=d[i];
	pthread_mutex_unlock(&mutex);
}	
return NULL;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please provide at least one argument.\n");
        exit(1);
    }

    int *digits = malloc(sizeof(int)* 10);
    pthread_t *thrds = malloc(sizeof(pthread_t) * (argc - 1));
    number *args = malloc(sizeof(data) * (argc - 1));
    pthread_mutex_t *mutex= malloc(sizeof(pthread_mutex_t));
    int i;
    if(0>pthread_mutex_init(&mutexes[i], NULL)){
	perror("Error on creating mutexes");
       exit(1);
        }
    for(i=0;i<10;i++){
	&digits[i]=0;
	}
    for (i = 0; i < argc - 1;i++) {
	args[i].digits = digits;
	args[i].mutex = mutex;
	args[i].nr = argv[i+1];
	if (0 > pthread_create(&thrds[i], NULL, func, (void *) &args[i])) {
            perror("Error on create thread");
        }
}
for (i = 0; i < argc - 1;i++) {
        if (0 > pthread_join(thrds[i], NULL)) {
            perror("Error waiting for thread");
        }
    }

for(i=0;i<10;i++){
	printf("%d: %d \n",i,&digits[1]);

}

pthread_mutex_destroy(&mutex);
free(args);
free(thrds);
free(digits);
return 0;
}
