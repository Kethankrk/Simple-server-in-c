#ifndef server_h
#define server_h

#include <netinet/in.h>
#include <sys/socket.h>


typedef struct Server {
    int domain;
    int type;
    int protocol;
    int port;
    int backlog;
    u_long interface;
    struct sockaddr_in address;

    int socket;

    void (*launch)(struct Server *server, char *msg);
} Server;


void launch(Server *server, char *msg);
Server server_connector(int domain, int type, int protocol, int port, int backlog, u_long interface, void (*launch)(Server *server, char *msg));

#endif