#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
/*
Un client trimite unui server doua siruri de caractere ordonate. Serverul va interclasa cele doua siruri si va 
returna clientului sirul rezultat interclasat.
*/
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

	if(connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la conectare\n");
		return 1;
	}

	char *unu = (char *)malloc(sizeof(char) * 200);
	if(!unu) {
		printf("Eroare malloc\n");
		return 1;
	}
	char *doi = (char *)malloc(sizeof(char) * 100);
	if(!doi) {
		printf("Eroare malloc\n");
		return 1;
	}

	scanf("%[^\n]%*c", unu);
	scanf("%[^\n]%*c", doi);

	uint16_t len_unu = strlen(unu), len_doi = strlen(doi);
	uint16_t len_result = len_unu + len_doi;
	len_unu = htons(len_unu); len_doi = htons(len_doi);

	send(c, &len_unu, sizeof(len_unu), 0);
	send(c, unu, sizeof(char) * strlen(unu), 0);
	send(c, &len_doi, sizeof(len_doi), 0);
	send(c, doi, sizeof(char) * strlen(doi), 0);

	free(doi);

	recv(c, unu, sizeof(char) * len_result, MSG_WAITALL);
	unu[len_result] = 0;

	printf("%s\n", unu);

	free(unu);
	close(c);
	
	return 0;
}