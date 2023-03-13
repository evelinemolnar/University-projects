
//Scrieti un program C care creeaza un proces fiu. Ambele procese vor rula pana cand
// primesc un semnal SIGUSR1. Implementati rutine pentru tratarea semnalului SIGUSR1
// astfel incat, daca procesul parinte primeste semnalul SIGUSR1 il va trimite si
// procesului fiu. Daca procesul fiu primeste un semnal SIGUSR1 fara ca procesul
// parinte sa primeasca semnalul, isi va incheia executia iar procesul parinte va apela
// wait pentru procesul fiu.
/*
 * Create a child process.
 * Both the child and parent processes will "work" an indefinite amount of time.
 * Implement a mechanism such that when the parent terminates, the child process also terminates without creating zombie processes.
 */
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
int f;
void child_handler(int sig) {
  printf("Child process terminating...\n");
  exit(0);
}

void parent_handler(int sig) {
  printf("Parent process terminating...\n");
  kill(f, SIGUSR1);
  wait(0);
  exit(0);
}

void zombie_handler(int sig) {
    printf("Parent waiting for child process to terminate\n");
    wait(0);
}

int main(int argc, char **argv) {
  f = fork();
  if (-1 == f) {
    perror("Error on fork");
  } else if (0 == f) {
    signal(SIGUSR1, child_handler);
    printf("C - Child PID: %d Parent PID: %d\n", getpid(),getppid());
    while(1) {
      printf("Child working...\n");
      sleep(3);
    }
    exit(0);
  } else {
    signal(SIGUSR1, parent_handler);
    signal(SIGCHLD, zombie_handler);
    printf("P - Child PID: %d Parent PID: %d\n", f, getpid());
    while(1) {
      printf("Parent working...\n");
      sleep(2);
    }
  }
  return 0;
}
