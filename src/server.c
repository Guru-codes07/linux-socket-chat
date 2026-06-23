#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#define BUFFER_SIZE 1024
int main()
{
  int server_socket, client_socket;
  char buffer[BUFFER_SIZE];
  
  // configuring server address
  struct sockaddr_in server_addr={0};
  server_addr.sin_family=AF_INET;
  server_addr.sin_port=htons(8080);
  server_addr.sin_addr.s_addr=INADDR_ANY;
  
  //creation of socket
   server_socket=socket(AF_INET,SOCK_STREAM,0);
  if(server_socket<0)
  {
    perror("socket failed");
    return 1;
    }
    
  // binding the socket with socket address
  if(bind(server_socket,(struct sockaddr *)&server_addr,sizeof(server_addr))<0)
  {
   perror("binding failed");
   return 1;
   }
  
  // listening for connections
  if(listen(server_socket , 5)<0)
  {
    perror("listen function failed");
    return 1;
  }
  printf("Server is listening on port 8080...\n");
  
  // configure client address
  struct sockaddr_in client_addr;
  socklen_t client_addr_len = sizeof(client_addr);
  
  // accepting client connection
  client_socket=accept(server_socket , (struct sockaddr *)&client_addr, &client_addr_len);
  if(client_socket<0)
  {
   perror("accept function failed");
   return 1;
  }
  printf("client connected! \n");
     
  // communication loop
  while(1)
{
 memset(buffer,0,BUFFER_SIZE);
 int bytes_received=recv(client_socket,buffer,BUFFER_SIZE,0);
 if(bytes_received == 0)
 {  printf("client disconnected\n");
    break;  
 }
 else if(bytes_received < 0)
 {
    perror("recv error");
    break;
  }
  printf("Client: %s\n", buffer);
  printf("You: ");
  fgets(buffer, BUFFER_SIZE, stdin);
  if(send(client_socket, buffer, strlen(buffer), 0)<0)
  {
    perror("send error");
    break;
  }
}
  close(client_socket);
  close(server_socket);
   
   return 0;
   }
