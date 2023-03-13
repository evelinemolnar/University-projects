#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>

void deservire_client(int c) {
  // deservirea clientului
	
    //struct sockaddr_in client;
    //socklen_t l;
    char s1[101];
 	  char s2[101];
    uint16_t l1,l2;
    //char caracter;
    uint16_t caracter;
    // deservirea clientului
    recv(c, &l1, sizeof(l1), MSG_WAITALL);
    l1 = ntohs(l1);
    recv(c, &l2, sizeof(l2), MSG_WAITALL);
    l2 = ntohs(l2);
    recv(c, &s1, sizeof(char) * l1, MSG_WAITALL);
    recv(c, &s2, sizeof(char) * l2, MSG_WAITALL);
    
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

int main() {
  int s;
  struct sockaddr_in server, client;
  int c;
  socklen_t l;
  
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
    c = accept(s, (struct sockaddr *) &client, &l);
    printf("S-a conectat un client.\n");
    if (fork() == 0) { // fiu
      deservire_client(c);
      return 0;
    }
    // se executa doar in parinte pentru ca fiul se termina mai sus din cauza exit-ului    
  }
}

