//Scrieti un program C care creeaza o ierarhie liniara de n procese (procesul
// parinte creeaza un proces fiu, care la randul lui creeaza un proces fiu, 
//samd.)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void f(int n) {
  if(n > 0) {
    int k = fork();
    if (k < 0) {
      perror("Error on fork");
      exit(1);
    } else if(k == 0) {
      printf("PID=%d - PPID=%d\n", getpid(), getppid());
      f(n-1);
    }
  }
  wait(0);
  exit(0);
}

int main(int argc, char **argv) {
  f(3);
  return 0;
}
 
