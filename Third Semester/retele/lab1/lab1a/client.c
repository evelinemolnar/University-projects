#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>


int main() {
  int c;
  struct sockaddr_in server;
  char s1[101] = { 0 };
  char s2[101] = { 0 };
  uint16_t nraparitii, caracter;
  
  c = socket(AF_INET, SOCK_STREAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");  //fprintf(stderr,"eroare")
    return 1;
  }
  
  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234);  //portul
  server.sin_family = AF_INET;  
  server.sin_addr.s_addr = inet_addr("127.0.0.1");// reprezentarea interna a adresei ip
  
  if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la conectarea la server\n");
    return 1;
  }


  printf("s1 : ");
  fgets(s1, 100, stdin);
  printf("s2 : ");
  fgets(s2, 100, stdin);
  

  send(c, (const char*)&s1, sizeof(s1), 0);
  send(c, (const char*)&s2, sizeof(s2), 0);
  //strcpy(s1, htons(s1));
  //strcpy(s2, htons(s2));
  recv(c, (char*) &caracter, sizeof(caracter), 0);
  recv(c, (char*) &nraparitii, sizeof(nraparitii), 0);
  caracter = ntohs(caracter);
  nraparitii = ntohs(nraparitii);
  printf("Caracterul este: %c \n", caracter);
  printf("Nr de aparitii: %hu\n", nraparitii);
  close(c);
}



//sau varianta 2

/*
Un client trimite unui server doua siruri de caractere. 
Serverul ii raspunde clientului cu caracterul care se regaseste de cele mai multe ori 
pe pozitii identice in cele doua siruri si cu numarul de aparitii ale acestui caracter.
*/



#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>

int main() {
  int c;
  struct sockaddr_in server;

  c = socket(AF_INET, SOCK_STREAM, 0);
  if(c < 0) {
    printf("Eroare la crearea socket-ului client\n");
    return 1;
  }

  memset(&server, 0, sizeof(server));
  server.sin_port = htons(4444);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");

  if(connect(c, (struct sockaddr *) &server, (socklen_t) sizeof(server)) < 0) {
    printf("Eroare la conectare\n");
    return 1;
  }

  char sir1[100], sir2[100];
  scanf("%[^\n]%*c", sir1);
  scanf("%[^\n]%*c", sir2);
  uint16_t len = ((strlen(sir1) > strlen(sir2)) ? strlen(sir2) : strlen(sir1));


  len = htons(len);
  send(c, &len, sizeof(len), 0);
  len = ntohs(len);
  send(c, sir1, sizeof(char) * len, 0);
  send(c, sir2, sizeof(char) * len, 0);
  
  uint16_t ch, maxim;
  recv(c, &maxim, sizeof(maxim), MSG_WAITALL);
  recv(c, &ch, sizeof(ch), MSG_WAITALL);

  ch = ntohs(ch);
  maxim = ntohs(maxim);

  printf("%c %hu", ch, maxim);
  
  close(c);

  return 0;
}