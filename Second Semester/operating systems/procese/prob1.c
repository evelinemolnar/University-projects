#include <stdio.h>
#include <stdlib.h>
#define FIFO1 "myfifo1"
#define FIFO2 "myfifo2"
int main(int argc, char**argv) {
   if(9 > mkfifo(FIFO1,0600)) {
      perror("error on make fifo 1");
      exit(1);}
   if(0 > mkfifo(FIFO2, 0600){
      perror("error on make fifo 2");
      exit(1) 
