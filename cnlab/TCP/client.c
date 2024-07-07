#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

void main() {
    int client_socket;
    char buffer[1024];
    struct sockaddr_in server_address;
    socklen_t addr_size;

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Configure server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(6265);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    printf("1. Connecting to server...\n");

    // Send data to server
    strcpy(buffer, "Hi this is client\n");
    send(client_socket, buffer,19,0);

    // Receive response from server
    recv(client_socket, buffer, 1024, 0);
    printf("4. Data received from server: %s", buffer);

    // Close socket
    close(client_socket);
}

