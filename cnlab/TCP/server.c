#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

void main() {
    int server_socket, new_socket;
    char buffer[1024];
    struct sockaddr_in server_address;
    struct sockaddr_storage client_address;
    socklen_t client_addr_size;

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Configure server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(6265);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind socket to address
    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    // Listen for incoming connections
    if (listen(server_socket, 5) == 0) {
        printf("Listening...\n");
    } else {
        printf("Error in listening.\n");
    }

    // Accept a connection
    client_addr_size = sizeof(client_address);
    new_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_addr_size);

    // Receive data from client
    recv(new_socket, buffer, 1024, 0);
    printf("Received data from client: %s\n", buffer);

    // Prepare and send response to client
    strcpy(buffer, "Hi this is the server\n");
    printf("Sending data to client...\n");
    send(new_socket, buffer, 21, 0);

    // Close sockets
    close(new_socket);
    close(server_socket);
}

