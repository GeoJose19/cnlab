#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

void main(){
    int sock_desc;
    struct sockaddr_in server_addr, client_addr;
    char serverMsg[200], clientMsg[200];
    int client_addr_len = sizeof(client_addr);
    
    // Create a UDP socket
    sock_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock_desc < 0) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    
    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(7777); // Server port
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address
    
    // Bind socket to server address
    if (bind(sock_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    
    printf("Server started. Listening...\n");
    
    while (1) {
        // Receive message from client
        if (recvfrom(sock_desc, clientMsg, sizeof(clientMsg), 0, (struct sockaddr*)&client_addr, &client_addr_len) < 0) {
            perror("Error receiving message");
            exit(EXIT_FAILURE);
        }
        printf("Message from client: %s\n", clientMsg);
        
        // Check if client wants to end the chat
        if (strcmp(clientMsg, "goodbye") == 0) {
            printf("Client said goodbye. Ending chat.\n");
            break;
        }
        
        // Prompt server to enter message to send to client
        printf("Enter message to send to client: ");
        fgets(serverMsg, sizeof(serverMsg), stdin);
        serverMsg[strcspn(serverMsg, "\n")] = '\0'; // Remove newline character
        
        // Send message to client
        if (sendto(sock_desc, serverMsg, strlen(serverMsg), 0, (struct sockaddr*)&client_addr, client_addr_len) < 0) {
            perror("Error sending message");
            exit(EXIT_FAILURE);
        }
        
        // Check if server wants to end the chat
        if (strcmp(serverMsg, "goodbye") == 0) {
            printf("Server said goodbye. Ending chat.\n");
            break;
        }
    }
    
    // Close socket
    close(sock_desc);
}

