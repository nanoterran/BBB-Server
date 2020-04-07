#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>

#define PORT 5050

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
  server.sin_port = htons( PORT );

  if( bind(socket_file_descriptor,(struct sockaddr *)&server , sizeof(server)) < 0)
  {
    perror("[-] Bind Failed");
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

  printf("[+] Connected...\n\n");

  int MAX_SIZE = 100;
  char read_buffer[MAX_SIZE];

  while(1)
  {
    int n = read(new_socket, read_buffer, sizeof(read_buffer));
    if (n < 0){
      perror("[-] ERROR: error reading from server socket.");
    }
    // read the message from client and copy it in buffer
    // read(socket_file_descriptor, read_buffer, sizeof(read_buffer));

    // print buffer which contains the client contents
    printf("From client: %s\t To client : ", read_buffer);
    bzero(read_buffer, MAX_SIZE);

    // copy server message in the buffer 
    while ((read_buffer[n++] = getchar()) != '\n');

    // // and send that buffer to client
    write(new_socket, read_buffer, sizeof(read_buffer));

    printf("Client sent: %s\n", read_buffer);

    // if msg contains "Exit" then server exit and chat ended.
    if (strncmp("exit", read_buffer, 4) == 0) {
      printf("Server Exit...\n");
      break;
    }
  }

  // After chatting close the socket
  close(socket_file_descriptor);

  return 0;
}