#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "Server.h"



Server server_connector(int domain, int type, int protocol, int port, int backlog, u_long interface, void (*launch)(Server *server, char *msg)){
    Server server;

    server.domain = domain;
    server.type = type;
    server.protocol = protocol;
    server.backlog = backlog;
    server.port = port;
    server.interface = interface;

    server.address.sin_family = domain;
    server.address.sin_port = htons(port);
    server.address.sin_addr.s_addr = htonl(interface);

    server.socket = socket(server.domain, server.type, server.protocol);
    if (server.socket == 0){
        perror("Failed to connect socket!!\n");
        exit(1);
    }

    if (bind(server.socket, (struct sockaddr *)&server.address, sizeof(server.address)) < 0){
        perror("Failed to bind socket!!\n");
        exit(1);
    }

    if(listen(server.socket, server.backlog) < 0){
        perror("Failed to listen!\n");
        exit(1);
    }

    server.launch = launch;
    return server;
}


void launch(Server *server, char *msg){
    printf("------| WAITING FOR CONNECTION |-------\n");
    int address_len = sizeof(server->address);
    int new_socket;
    char buffer[30000];

    while(1){
        new_socket = accept(server->socket, (struct sockaddr*)&server->address, (socklen_t *)&address_len);
        read(new_socket, buffer, 30000);
        printf("%s\n", buffer);

        write(new_socket, msg, strlen(msg));
        close(new_socket);
    }
}