#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

void reverseString(char *str){
	int l=strlen(str);
	for(int i=0;i<l/2;i++){
		char temp=str[i];
		str[i]=str[l-i-1];
		str[l-i-1]=temp;
	}
}


void main(){
    int server,newSock;
    char buffer[1024];
    struct sockaddr_in servAddr;
    struct sockaddr_storage store;
    socklen_t addrSize;
    server=socket(AF_INET,SOCK_STREAM,0);
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(6279);
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
    	char temp[100];
    	strcpy(temp,buffer);
    	reverseString(buffer);
	printf("Reversed String is %s\n",buffer);
	if(strcmp(temp,buffer)==0){
		printf("Pallidnrome\n");
	}
	else{
		printf("Not pallindrome\n");
	}
    	send(newSock,buffer,sizeof(buffer),0);
	if(strcmp(buffer,"goodbye")==0){
    		printf("Server said goodbye\n");
    		break;
    	}
    	
    	
    }
    
    close(newSock);
    close(server);
}
