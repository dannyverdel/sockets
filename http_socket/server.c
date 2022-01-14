/* author: Danny Verdel */

//
// Created by Danny Verdel on 14/01/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>

#include <netinet/in.h>

int main() {
    // open a file to serve
    int c;
    FILE *html_data;
    html_data = fopen("../index.html", "r");

    // read contents of html file into buffer
    char response_data[3000];
    while ((c = getc(html_data)) != EOF)
        strcat(response_data, (const char *) &c);

    fclose(html_data);

    char http_header[6000] = "HTTP/1.1 200 OK\r\n\n";

    strcat(http_header, response_data);

    // create a socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // define the address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(7071);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int bind_status = bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    if(bind_status == -1) {
        printf("Something went wrong while binding the socket to the server address.\n");
        exit(-1);
    }

    listen(server_socket, 5);

    int client_socket;
    while(1) {
        client_socket = accept(server_socket, NULL, NULL);
        send(client_socket, http_header, sizeof(http_header), 0);
        close(client_socket);
    }

    return 0;
}