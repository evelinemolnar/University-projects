//Scrieti un program C care genereaza N numere intregi aleatoate (N dat la linia de 
//comanda).Apoi creeaza un proces fiu si ii trimite numerele prin pipe. 
//Procesul fiu calculeaza media numerelor si trimite rezultatul inapoi parintelui. 

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char* argv[]){
	if(argc!=2){
	printf("Please provide at least one argument");
	exit(1);
}
	int p2c[2],c2p[2];
	pipe(p2c);
	pipe(c2p);
	int f=fork();
	if(f==-1){
		perror("Error on fork ");
        	exit(1);
	}
	else if (f==0){
		close(p2c[1]);
		close(c2p[0]);
		int n=0,i,nr;
		float rez=0;
		if(read(p2c[0],&n, sizeof(int))<0){
			perror("Error on read n from parent to child");
			close(p2c[1]);
			close(c2p[0]);
			exit(1);
		}
		for(i=0;i<n;i++){
			if(read(p2c[0],&nr, sizeof(int))<0){
			perror("Error on read nr from parent to child");
                	close(p2c[1]);
                	close(c2p[0]);
                	exit(1);
		}
		rez=rez+nr;
		}
		rez=rez/n;
		if(write(c2p[1],&rez, sizeof(float))>0){
			perror("Error on write result to parent ");
            		close(p2c[0]);
            		close(c2p[1]);
            		exit(1);}
		close(p2c[0]);
                close(c2p[1]);
                exit(0);
	}
	else{
		close(p2c[0]);
		close(c2p[1]);
		int n = atoi(argv[1]);
		int i,nr;
		float rez=-1;
		srandom(time(0));
		if(0 > write(p2c[1], &n, sizeof(int))) {
	            perror("Error on write n to child ");
        	    close(p2c[1]);
           	    close(c2p[0]);
               	    wait(0);
           	    exit(1);
       		 }
		for(i = 0; i < n; i++) {
            // limit the number generation between 0 and 99 just so we can easily check that the calculation is correct
            nr = random() % 100;
            printf("Parent generated %d\n", nr);
            if(0 > write(p2c[1], &nr, sizeof(int))) {
                perror("Error on write number to child ");
                close(p2c[1]);
                close(c2p[0]);
                }
		}
	wait(0);

        if(0 > read(c2p[0], &rez, sizeof(float))) {
            perror("Error on read result from child ");
        }
        printf("Average is %f\n", rez);
        close(p2c[1]);
        close(c2p[0]);
    }
    return 0;
			

}   
