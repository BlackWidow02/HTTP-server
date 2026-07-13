#include <stdio.h>
#include <unistd.h>
#include "tcp.h"

int main() {
    //server binds to port 8080
    tcp_server server = {0};
    server_status_e status = bind_tcp_port(&server, 8080);
    if(status != SERVER_OK){
        printf("Sever connection failure\n");
        return -1;
    }

    //waits for connection
    //once connected print "Client Connected"

    int client_fd = accept_client(server.socket_fd);
    if(client_fd == -1){
        printf("Failed to accept client connection\n");
        close(server.socket_fd);
    }

    printf("Client Connected\n");
    close(client_fd);
    close(server.socket_fd);
    return 0;
}