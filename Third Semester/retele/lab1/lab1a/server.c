#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
 

int main() {
  int s;
  struct sockaddr_in server, client;
  int c;
  socklen_t l;
  char s1[101];
  char s2[101];
  
  
  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0) {
    printf("Eroare la crearea socketului server\n");
    return 1;
  }
  
  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  
  if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la bind\n");
    return 1;
  }
 
  listen(s, 5);
  
  l = sizeof(client);
  memset(&client, 0, sizeof(client));
  
  while (1) {
    
    //char caracter;
    uint16_t caracter;
    c = accept(s, (struct sockaddr *) &client, &l);
    printf("S-a conectat un client.\n");
    // deservirea clientului
    recv(c, (char*)&s1, sizeof(s1), MSG_WAITALL);
    recv(c, (char*)&s2, sizeof(s2), MSG_WAITALL);
    //printf("%s",s1);
    //printf(" %s",s2);
    //strcpy(s1, ntohs(s1));
    //strcpy(s2, ntohs(s2));

    //cerinta 10
    int i;
    int nraparitii = 0;
    int freq[256] ; 
    int ascii;
    
    for(i=0; i<255; i++)  //Set frequency of all characters to 0
    {
        freq[i] = 0;
    }


    for(i = 0; i < s1[i] != '\0'; i++)
    {
      if(s1[i]==s2[i])          //daca caracterele de pe aceeasi pozitie sunt egale
        {
          ascii = (int)s1[i];     // aflam codul ascii al caracterului
          freq[ascii] += 1;       // in vectorul de frecventa, pozitia codului ascii creste
        }
    }
    int max =0;

    for(i = 0; i < 255; i++)
    {
      
      if(freq[i] > freq[max])   
          max = i;              //codul ascii al caracterului
      
    }

    caracter= max;
    caracter=htons(caracter);
    nraparitii=freq[max];
    nraparitii=htons(nraparitii);
    

    send(c, &caracter, sizeof(caracter), 0);
    send(c,&nraparitii, sizeof(nraparitii),0 );
    close(c);
    // sfarsitul deservirii clientului;
  }
}


//sau varianta 2


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
  int s, c, l;
  struct sockaddr_in server, client;
  
  s = socket(AF_INET, SOCK_STREAM, 0);
  if(s < 0) {
    printf("Eroare la crearea socket-ului server\n");
    return 1;
  }

  memset(&server, 0, sizeof(server));
  server.sin_port = htons(4444);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;

  if(bind(s, (struct sockaddr *) &server, (socklen_t) sizeof(server)) < 0) {
    printf("Eroare la bind\n");
    return 1;
  }

  listen(s, 5);
  l = sizeof(client);
  memset(&client, 0, sizeof(client));

  while(1) {
    c = accept(s, (struct sockaddr *) &client, (socklen_t *) &l);
    printf("S-a conectat un client.\n");

    uint16_t len;
    char sir1[100], sir2[100];
    recv(c, &len, sizeof(len), MSG_WAITALL);
    len = ntohs(len);

    recv(c, sir1, sizeof(char) * len, MSG_WAITALL);
    recv(c, sir2, sizeof(char) * len, MSG_WAITALL);
    sir1[len] = sir2[len] = 0;

    uint16_t freq[129], i, maxim = 0, ch_max = 0;
    memset(freq, 0, sizeof(uint16_t) * 129);

    for(i = 0;i < len;++i) {
      if(sir1[i] == sir2[i]) {
        freq[(uint16_t)sir1[i]]++;
        if(freq[(uint16_t)sir1[i]] > maxim) {
          maxim = freq[(uint16_t)sir1[i]];
          ch_max = sir1[i];
        }
      }
    }

    ch_max = htons(ch_max);
    maxim = htons(maxim);

    send(c, &maxim, sizeof(maxim), 0);
    send(c, &ch_max, sizeof(ch_max), 0);

    close(c);
  }
  
  
  return 0;
}