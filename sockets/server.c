/* author: Danny Verdel */

//
// Created by Danny Verdel on 13/01/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main(int argc, char **argv) {
    char server_message[256] = "You have reached the server!";

    // create the server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0); //socket(int domain, int type, int protocol)

    // define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET; // Has to be the same as the domain of the socket
    server_address.sin_port = htons(9002); //htons() translates a short integer from host byte order to network byte order
    server_address.sin_addr.s_addr = INADDR_ANY;

    // bind the socket to our specified IP and port
    int bind_status;
    bind_status = bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    if(bind_status == -1) {
        printf("Something went wrong while binding the socket to the server address.\n\n");
        exit(-1);
    }

    listen(server_socket, 5); // listen(int socket, int backlog) backlog defines the maximum length for the queue of pending connections

    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    // send the message
    send(client_socket, server_message, sizeof(server_message), 0);

    // close the socket
    close(server_socket);

    return 0;
}