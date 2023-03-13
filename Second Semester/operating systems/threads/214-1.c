/*
Se da n si m, un thread principal initializeaza un sir de n elemente cu nr random
intre 100-1000, dupa n thread-uri fac de m ori : genereaza un index random intre 0 si n-1 si verifica daca poz din sir de pe index ii cifra, daca nu, face suma cifrelor si inlocuieste pozitia aia 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>


tydef struct {
	int *arr, n, m;
	pthread_mutex_t *mutex;
	pthread_barrier_t *barrier;
}data;

void *f(void *arg){
	data d = *((data*)arg);
	pthread_barrier_wait(d.barrier);
	int i, nr, aux, sum;
	sum=0;
	for(i=0;i<d.m;i++){
		pthread_mutex_lock(d.mutex);
		nr = random()%d.n;
		if(d.arr[nr]>9)
		{
		aux=d.nr;
		while(aux>0){
			sum=sum+aux%10;
			aux=aux/10;
		}
		d.arr[nr] = sum;
		pthread_mutex_unlock(d.mutex);
		}
		pthread_mutex_unlock(d.mutex);
	}
	return NULL;

}


int main(int argc, char *argv[]{
if (argc!=3){
	printf("Dati 2 argumente");
	exit(1);
}

int n=atoi(argv[1]);
int m=atoi(argv[2]);
int *arr = malloc(sizeof(int)*n);
pthread_mutex_t *mutex=malloc(sizeof(pthread_mutex_t));
pthead_mutex_init(m,NULL);
pthread_barrier_t *barrier = malloc(sizeof(pthread_barrier_t));
pthread_barrier_init(b,NULL,n);
pthread_t *th = malloc(sizeof(pthread_t)*n);
data *args = malloc(sizeof(data)*n);
int i;
srandom(time(NULL));
for(i=0;i<n;i++){
	arr[i]=100+random()%(901);
	printf("%d " , arr[i]);
}
printf("\n");

for(i=0;i<=n;i++){
	args[i].arr =arr;
	args[i].n = n;
	args[i].m=m;
	args[i].mutex=mutex;
	args[i].barrier=barrier;
	pthread_create(&th[i],NULL,f,&args[i]);
}

for(i=0;i<=n;i++){
	pthread_join(th[i],NULL);
}

for(i=0;i<=n;i++){
	printf("%d " , arr[i]);
}


pthread_mutex_destroy(mutex);
pthread_barrier_destroy(barrier);
free(arr);
free(args);
free(mutex);
free(barrier);
free(th);


return 0;
}

