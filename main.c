#include<stdio.h>
#include "Server.h"


int main(void){
    char *msg = "This is a server made with C";
    Server server = server_connector(AF_INET, SOCK_STREAM, 0, 80, 20, INADDR_ANY, launch);
    server.launch(&server, msg);
    return 0;
}