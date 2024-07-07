#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>

void main()
{
    int server;
    struct sockaddr_in servAddr, client_addr;
    char servMsg[2000], cliMsg[2000];
    int client_struct_length = sizeof(client_addr);
    
    // Create a UDP socket
    server = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(server < 0)
    {
        printf("Error while creating socket \n");
        exit(1);
    }
    printf("Socket created successfully\n");

    // Prepare the server address structure
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(2002); // Port number 2002
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Localhost IP address

    // Bind the socket to the server address
    if(bind(server, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0)
    {
        printf("Couldn't bind to the port \n");
        exit(1);
    }
    printf("Binding done\n");
    printf("Listening...\n\n");

    // Receive message from client
    if (recvfrom(server, cliMsg, sizeof(cliMsg), 0, (struct sockaddr*)&client_addr, &client_struct_length) < 0)
    {
        printf("Couldn't receive\n");
        exit(1);
    }
    printf("Msg from client: %s\n", cliMsg);

    // Prompt user to enter a message to send back to client
    printf("Enter message to send back to client: ");
    fgets(servMsg, sizeof(servMsg), stdin);
    servMsg[strcspn(servMsg, "\n")] = '\0'; // Remove newline character from input

    // Send message back to client
    if (sendto(server, servMsg, strlen(servMsg), 0, (struct sockaddr*)&client_addr, client_struct_length) < 0)
    {
        printf("Can't send\n");
        exit(1);
    }

    // Close the server socket
    close(server);
}

