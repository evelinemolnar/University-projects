#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t m;
int n = 500;
void* F(void* a) {
    while(1){
         pthread_mutex_lock(&m);
         if(n<0||n>1000){
            pthread_mutex_unlock(&m);
            return NULL;
         }
         n+=random()%1000-500;
         pthread_mutex_unlock(&m);
    }
    return NULL;
}


int main(int argc, char** argv) {
    
    pthread_mutex_init(&m,NULL);
    pthread_t TH[2];

    pthread_create(&TH[0],NULL,F,NULL);
    pthread_create(&TH[1],NULL,F,NULL);

    pthread_join(TH[0],NULL);
    pthread_join(TH[1],NULL);

    pthread_mutex_destroy(&m);
   
return 0; }
