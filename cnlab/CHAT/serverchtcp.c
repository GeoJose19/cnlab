#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
void main(){
    int server,newSock;
    char buffer[1024];
    struct sockaddr_in servAddr;
    struct sockaddr_storage store;
    socklen_t addrSize;
    server=socket(AF_INET,SOCK_STREAM,0);
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(6268);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    bind(server,(struct sockaddr *)&servAddr,sizeof(servAddr));
    if(listen(server,5)==0){
        printf("Listening\n");
    }else{
        printf("Error\n");
    }
    newSock=accept(server,(struct sockaddr *)&store,&addrSize);
    while(1){
    	recv(newSock,buffer,sizeof(buffer),0);
    	if(strcmp(buffer,"goodbye")==0){
    		printf("Client said goodbye\n");
    		break;
    	}
    	printf("Message from client: %s\n",buffer);
    	bzero(buffer,1024);
    	printf("Enter message to send to client: ");
    	fgets(buffer,sizeof(buffer),stdin);
    	buffer[strcspn(buffer,"\n")]='\0';
    	send(newSock,buffer,sizeof(buffer),0);
	if(strcmp(buffer,"goodbye")==0){
    		printf("Server said goodbye\n");
    		break;
    	}
    	
    	
    }
    
    close(newSock);
    close(server);
}
