#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

void main(){
    int client_sock;
    struct sockaddr_in server_addr;
    char serverMsg[200], clientMsg[200];
    int server_addr_len = sizeof(server_addr);
    
    // Create a UDP socket
    client_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (client_sock < 0) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    
    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(7777); // Server port
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address
    
    while (1) {
        // Prompt user to enter message to send to server
        printf("Enter message to send to server: ");
        fgets(clientMsg, sizeof(clientMsg), stdin);
        clientMsg[strcspn(clientMsg, "\n")] = '\0'; // Remove newline character
        
        // Send message to server
        if (sendto(client_sock, clientMsg, strlen(clientMsg), 0, (struct sockaddr*)&server_addr, server_addr_len) < 0) {
            perror("Error sending message");
            exit(EXIT_FAILURE);
        }
        
        // Check if client wants to end the chat
        if (strcmp(clientMsg, "goodbye") == 0) {
            printf("Client said goodbye. Ending chat.\n");
            break;
        }
        
        // Receive message from server
        if (recvfrom(client_sock, serverMsg, sizeof(serverMsg), 0, (struct sockaddr*)&server_addr, &server_addr_len) < 0) {
            perror("Error receiving message");
            exit(EXIT_FAILURE);
        }
        
        printf("Message from server: %s\n", serverMsg);
        
        // Check if server wants to end the chat
        if (strcmp(serverMsg, "goodbye") == 0) {
            printf("Server said goodbye. Ending chat.\n");
            break;
        }
    }
    
    // Close socket
    close(client_sock);
}

