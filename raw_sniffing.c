#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "hacking.h"

void main(){
	int sock, recv_lenght;
	unsigned char buf[9000];

	sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
	if(sock < 0)
		fatal("IN SOCKET");

	for(int i=0; i<3 ; i++){
		recv_lenght = recv(sock, buf, 8000, 0);
		printf("Got a %d byte packet\n", recv_lenght);
		dump(buf, recv_lenght);
	}
}
