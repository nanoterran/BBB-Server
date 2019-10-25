#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
  struct sockaddr_in server;
  struct sockaddr_in client;

  int socket_file_descriptor = socket(AF_INET , SOCK_STREAM , 0);
  if(socket_file_descriptor == -1)
  {
    perror("[-] ERROR: Could not create socket");
    exit(1);
  }

  //Prepare the sockaddr_in structure
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons( 5050 );

  if( bind(socket_file_descriptor,(struct sockaddr *)&server , sizeof(server)) < 0)
  {
    perror("[-] ERROR: Bind Failed");
    exit(1);
  }
  puts("[+] Done Binding");

  // Wait for client to connect
  listen(socket_file_descriptor , 1);

  //Accept and incoming connection, and only accept one client
  puts("[i] Waiting for incoming connections...");

  socklen_t client_length = sizeof(struct sockaddr_in);

  int new_socket = accept(
      socket_file_descriptor,
      (struct sockaddr *)&client,
      &client_length);
  
  if(new_socket < 0)
  {
    perror("[-] ERROR: Could not accept connection");
  }

  puts("[+] Conected");

  return 0;
}