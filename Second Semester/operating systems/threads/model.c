#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

tydef struct {
        int *arr, n;
	//int m;
        pthread_mutex_t *mutex;
        //pthread_barrier_t *barrier;
	//pthread_cond_t *cond;
}data;

void *f(void *arg){
	 data d = *((data*)arg);
	//functia ce se executa in thread, eventual, daca e nevoie pun
	//pthread_barrier_wait(d.barrier);
	//apoi in zona critica unde sunt modificari, mutex lock si unlock 
	//bariera se pune inainte de lock, cond, dupa 
	// ex: if (*(d.index) % 2 != 0) pthread_cond_wait(d.cond, d.mutex);
	// la sf pthread_cond_signal(d.cond); apoi unlock mutex


	return NULL;
}

int main(int argc, char *argv[]{
	if (argc!=3){
        printf("Dati 2 argumente");
        exit(1);
	}

	//srandom(time(NULL));
    	int n = atoi(argv[1]);   convert char to int 
	//daca se dau argumentele de la apel, altfel se citesc cu scanf
	int *arr = malloc(sizeof(int)*n);
pthread_mutex_t *mutex=malloc(sizeof(pthread_mutex_t));
pthead_mutex_init(m,NULL);
pthread_barrier_t *barrier = malloc(sizeof(pthread_barrier_t));
pthread_barrier_init(b,NULL,n);
pthread_t *th = malloc(sizeof(pthread_t)*n);
data *args = malloc(sizeof(data)*n);



//pthread_create(&th[i],NULL,f,&args[i]);



//pthread_join(th[i],NULL);




pthread_mutex_destroy(mutex);
pthread_barrier_destroy(barrier);
free(arr);
free(args);
free(mutex);
free(barrier);
free(th);
return 0;


}

