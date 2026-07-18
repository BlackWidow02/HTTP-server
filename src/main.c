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
        return -1;
    }

    printf("Client Connected\n");
    

    //receive HTTP headers from server
    //ssize_t recv(int sockfd, void buf[size], size_t size, int flags);
    // char buff [8192]; //buffer size based off of apache server
    // ssize_t bytes_read = recv(client_fd, buff, sizeof(buff) - 1, 0);
    // parse_request(&bytes_read);

    //pass to paser function and then close out

    close(client_fd);
    close(server.socket_fd);
    return 0;
}

