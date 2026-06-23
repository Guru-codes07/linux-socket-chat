#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>  
#include<arpa/inet.h>
#include<unistd.h>
#define BUFFER_SIZE 1024
int main()
{
    // declaring the required things
    int client_socket;
    char buffer[BUFFER_SIZE];

    // configure the server address
    struct sockaddr_in server_addr={0};
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(8080);
     if( inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr)<=0)
     {
        perror("invalid address");
        return 1;
     }
     
     // socket creation 
     client_socket=socket(AF_INET,SOCK_STREAM,0);
     if(client_socket<0)
     {
        perror("socket creation failed");
        return 1;
     }

     // connecting the socket
     if(connect(client_socket,(struct sockaddr *)&server_addr,sizeof(server_addr))<0)
     {
        perror("connection failed");
        return 1;
     }
        printf("connected to the server! \n");
    
    // while loop of messages
    while(1)
    {
        printf("Enter message to send to server: ");
        fgets(buffer,BUFFER_SIZE,stdin);
        buffer[strcspn(buffer,"\n")]=0; // remove newline character

        // send the message to the server
        if(send(client_socket,buffer,strlen(buffer),0)<0)
        {
            perror("send failed");
            return 1;
        }

        // receive response from the server
        memset(buffer,0,BUFFER_SIZE);
        int bytes_received=recv(client_socket,buffer,BUFFER_SIZE,0);
        if(bytes_received<=0)
        {
            perror("recv failed");
            return 1;
        }
        printf("Message from server: %s\n",buffer);
    }    
    close(client_socket);
    return 0;
} 
