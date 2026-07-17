#ifndef TCP_H
#define TCP_H

#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    int socket_fd;
    struct sockaddr_in address;
} tcp_server;

// Changed return type from server_status_e to int
int bind_tcp_port(tcp_server *server, int port);
int accept_client(int server_fd);

#endif // TCP_H