#include "tcp.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h> // Added for close()

int bind_tcp_port(tcp_server *server, int port) {
    // 1. INPUT VALIDATION: Validate inputs BEFORE modifying struct state
    if (server == NULL || port < 1 || port > 65535) {
        return -1; // Explicit standard failure indicator
    }
    
    // 2. Clear state safely
    memset(server, 0, sizeof(*server)); 
    server->socket_fd = -1;
    
    // 3. Socket creation
    server->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->socket_fd == -1) {
        perror("socket creation failed!\n");
        return -1; 
    }

    // 4. Address assignment
    server->address.sin_family = AF_INET;
    server->address.sin_addr.s_addr = INADDR_ANY; 
    server->address.sin_port = htons(port);       

    // 5. Bind socket
    int socket_bind = bind(server->socket_fd, (struct sockaddr *)&server->address, sizeof(server->address));
    if (socket_bind == -1) {
        perror("binding to socket failed!\n");
        close(server->socket_fd); 
        server->socket_fd = -1; 
        return -1; 
    }

    // 6. Listen
    int socket_listen = listen(server->socket_fd, 5);
    if (socket_listen == -1) {
        perror("listening on socket failed!\n");
        close(server->socket_fd); 
        server->socket_fd = -1; 
        return -1; 
    }

    return 0; // Standard POSIX Success
}