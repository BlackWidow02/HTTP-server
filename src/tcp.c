#include "tcp.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>


server_status_e bind_tcp_port(tcp_server *server, int port){
    //create a socket which will return a file descriptor
    //domain is AF_INET
    //type is SOCK_STREAM
    //protocal is 0
   

    memset(server, 0, sizeof(*server)); //zero out all fields first
    server->socket_fd = -1;
    
    server->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server->socket_fd == -1){
        perror("socket creation failed!\n");
        return SERVER_SOCKET_ERROR;
    }


    //create the address for the bind
    server->address.sin_family = AF_INET; //.sin_family is always set to AF_INET
    server->address.sin_addr.s_addr = INADDR_ANY; //bound to all local interfaces
    server->address.sin_port = htons((uint16_t)port);       //convert port to network byte order

    //bind the addr to the socket
    //sockfd == file desciptor
    //server->address
    int socket_bind = bind(server->socket_fd, (struct sockaddr *)&server->address, sizeof(server->address));
    if(socket_bind == -1){
        perror("binding to socket failed!\n");
        close(server->socket_fd); //added this line
        server->socket_fd = -1; //added this line
        return SERVER_BIND_ERROR;
    }

    //listen
    //
    int socket_listen = listen(server->socket_fd, 5);
    if(socket_listen == -1){
        perror("listening on socket failed!\n");
        close(server->socket_fd); 
        server->socket_fd = -1; 
        return SERVER_LISTEN_ERROR;
    }

    return SERVER_OK;
}

    //accept the connection
    //int accept(int sockfd, struct sockaddr *_Nullable restrict addr,
    //   socklen_t *_Nullable restrict addrlen);
  int accept_client(int server_fd){
        struct sockaddr_in client_address = {0}; //inialize output buffer to 0
        socklen_t client_len = sizeof(client_address);

        int client_fd = accept(server_fd, (struct sockaddr *)&client_address, &client_len);
        if (client_fd == -1) {
            perror("accept failed!\n");
            return -1;
        }

        return client_fd;
    }