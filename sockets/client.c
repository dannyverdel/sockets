#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#define BUFFER_SZ 256

int main() {
    //create a socket
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0); //socket(int domain, int type, int protocol)

    // specify an address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET; // Has to be the same as the domain of the socket
    server_address.sin_port = htons(9002); //htons() translates a short integer from host byte order to network byte order
    server_address.sin_addr.s_addr = INADDR_ANY;

    int connection_status;
    connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    // check for error with the connection
    if(connection_status == -1) {
        printf("Something went wrong while connecting to the remote socket.\n\n");
        exit(-1);
    }

    // receive data from the server
    char server_response[BUFFER_SZ];
    recv(network_socket, &server_response, sizeof(server_response), 0);

    // print out the server's response
    printf("The server sent the data: %s\n", server_response);

    // close the socket
    close(network_socket);

    return 0;
}