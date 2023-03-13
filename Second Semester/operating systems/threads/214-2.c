#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

//Se da n si m, un thread princ initializeaza un sir de n elemente cu nr
//random intre 100-1000, dupa n threaduri fac de m ori  asta: genereaza un
//index random intre 0 si n-1 si verifica daca poz din sir de pe index ii cifra, 
//daca nu, face suma cifrelor si inlocuieste pe poz aia
 
typedef struct{
   pthread_mutex_t *mutex;
   int *arr;
   int n,m,id;
}data;

void *f(void *arg)
{
   data d=*((data*) arg);
   int i;
   pthread_mutex_lock(d.mutex);
   for(i=0;i<d.m;i++)
   {
        int nr2=rand()%d.n;
        printf("TH[%d] verifica ARR[%d]=%d \n",d.id,nr2,d.arr[nr2]);
        if(d.arr[nr2]>9)
        {
            int x=d.arr[nr2];
            int sum=0;
            while(x!=0)
            {
                sum=sum+x%10;
                x=x/10;
            }
            d.arr[nr2]=sum;
        }
        int i2;
        printf("Sirul: ");
        for (i2 = 0; i2 < d.n; i2++) 
	  {
            printf("%d ", d.arr[i2]);
        }
        printf("\n");
   }
   pthread_mutex_unlock(d.mutex);
   return NULL;
}

int main(int argc, char *argv[])
{
   if(argc!=3)
   {
       printf("provide two arg \n");
       exit(1);
   }
   srandom(time(NULL));
   int n=atoi(argv[1]);
   int m=atoi(argv[2]);
   int *arr=malloc(sizeof(int)*n);

   int i,nr;
   printf("Sirul: ");
   for(i=0;i<n;i++)
   {
       nr=(rand()%901+100);
       arr[i]=nr;
       printf("%d ",arr[i]);
   }
   printf("\n");
   pthread_mutex_t *mutex=malloc(sizeof(pthread_mutex_t));
   pthread_mutex_init(mutex,NULL);
 
   pthread_t *th=malloc(sizeof(pthread_t)*n);
   data *args=malloc(sizeof(data)*n);
   for(i=0;i<n;i++)
   {
       args[i].id=i;
       args[i].mutex=mutex;
       args[i].n=n;
       args[i].m=m;
       args[i].arr=arr;
       pthread_create(&th[i],NULL,f,&args[i]);
   }
   for(i=0;i<n;i++)
        pthread_join(th[i],NULL);
   pthread_mutex_destroy(mutex);
   free(th);
   free(args);
   free(mutex);
   free(arr);
   return 0;
}
