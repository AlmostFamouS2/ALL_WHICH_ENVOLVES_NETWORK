#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <pthread.h>
#include "hacking.h"

#define PORTA 4444
#define CONEXOES 5
#define MAX 1024

struct Sock {
	int sock;
	struct sockaddr_in addr;
	char name[32];
	socklen_t len;
	int id;
};

int err(const char *msg){
	fprintf(stderr, "%s\n", msg);
	exit(1);
}

unsigned int clicount = 0;
struct Sock clientes[CONEXOES];
void *recv_msg(void *clientsock);

int main(int argc, char *argv[]){
	if ( ! *++argv) { fprintf(stderr, "DIGITE UMA PORTA COMO ARGUMENTO!\n");  return 1;}

	pthread_t thread[CONEXOES];
	// int PORTA = atoi(argv[1]);   NAO FUNCIONA !!!!
	const char automsg[] = "Seja bem vindo ao chat !!!!\n Digite o seu name por gentileza: ";
	char msgcli[MAX], msgsrv[MAX] = {0};

	int sock = socket(AF_INET, SOCK_STREAM, 0);

	if(sock < 0)
		err("ERRO AO CRIAR O SOCKET!");

	struct sockaddr_in srv = {0}, cli = {0};
		srv.sin_family = AF_INET;
		srv.sin_port = htons(PORTA);
		srv.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (bind(sock, (struct sockaddr *)&srv, sizeof(srv)) < 0)
		err("ERRO NA EXECUCAO DO BIND NESSA PORTA !");
	if(listen(sock, CONEXOES) < 0)
		err("ERRO AO OUVIR 5 CONEXOES!");
	puts("[INFO] SERVIDOR INICIALIZADO COM SUCESSO!");
	printf("OUVINDO NA PORTA: %d\n", PORTA);

	while(clicount != CONEXOES){
		clientes[clicount].len = sizeof(clientes[clicount].addr);
		clientes[clicount].sock = accept(sock, 
									(struct sockaddr *)&clientes[clicount].addr,
									&clientes[clicount].len);

	if(clientes[clicount].sock < 0)
		puts("ERRO AO TENTAR ACEITAR CONEXAO !");

	send(clientes[clicount].sock, &automsg, sizeof(automsg), 0);   // Mensagem de boas vindas

	int temp = recv(clientes[clicount].sock, msgcli, MAX, 0);
		if(temp < 0)
			err("[ERROR] ERRO AO TENTAR LER O SOCKET");

	clientes[clicount].id = clicount;
	memcpy(clientes[clicount].name, msgcli, strlen(msgcli));
	
	memcpy(msgsrv, "Bem-Vindo\n", 10);
	strncat(msgsrv, msgcli, sizeof(clientes[clicount].name));   // Se der errado, o erro ta aqui
	strcat(msgsrv, "\nVoce Foi registrado com sucesso!\n");

	send(clientes[clicount].sock, &msgsrv, sizeof(msgsrv), 0); // Enviando resposta do 1 recebimento
	memset(&msgcli, '\0', MAX);

	int status = pthread_create(&thread[clicount], NULL, recv_msg, (void *)clientes[clicount].sock);
		if(status) {
			fprintf(stderr, "[ERROR] ERRO ao tentar criar a Thread!");
			close(clientes[clicount].sock);
			return EXIT_FAILURE;
		}
	sleep(3);
	clicount++;
}

return 0;
}

void *recv_msg(void *clientsock){
	int sock = clientsock;
	int size;
	char msg[MAX];
	char msgconc[MAX];
	int x = clicount;
	
	while( (size = recv(sock, msg, MAX, 0)) > 0){
		if(strstr(msg, "!quit")){
			close(sock);
			puts("CONEXAO FECHADA!");
			break;
		}

	printf("%s: %s", clientes[x].name, msg);
	dump(msg, strlen(msg));
	puts("\n");
	strncpy(msgconc, clientes[x].name, sizeof(msgconc));
	strncat(msgconc, ": ", sizeof(msgconc)-1);
	strncat(msgconc, msg, sizeof(msgconc)-1);
	strncat(msgconc, "\n", sizeof(msgconc)-1);

	for(int i = 0; i < clicount; i++)
		if ( i != x)  // If the client isn't the sender
			send(clientes[i].sock, msgconc, sizeof(msgconc), 0);

	memset(&msg, '\0', MAX);
	memset(&msgconc, '\0', MAX);

	if(size == 0)
		printf("%s: Cliente desconetou!\n", clientes[x].name);
	}
}
