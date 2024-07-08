#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
void main(){
    int client;
    char buffer[1024];
    struct sockaddr_in servAddr;
    socklen_t addrSize;
    client=socket(AF_INET,SOCK_STREAM,0);
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(6268);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    connect(client,(struct sockaddr *)&servAddr,sizeof(servAddr));
    
    
    while(1){
    
    	printf("Enter message to send to server: ");
    	fgets(buffer,sizeof(buffer),stdin);
    	buffer[strcspn(buffer,"\n")]='\0';
    	send(client,buffer,sizeof(buffer),0);
	if(strcmp(buffer,"goodbye")==0){
    		printf("Client said goodbye\n");
    		break;
    	}
    	
    	
    	bzero(buffer,1024);
    	
    	recv(client,buffer,1024,0);
    	if(strcmp(buffer,"goodbye")==0){
    		printf("Server said goodbye\n");
    		break;
    	}
    	printf("Message from server: %s\n",buffer);
    	
    	
    	
    }
    
    close(client);

}
