
#include <stdio.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 5050

int main(int argc, char const *argv[]) 
{
	int socket_file_descriptor = 0;
	int valread;
	struct sockaddr_in server;  
	char buffer[1024] = {0};

	if ((socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
			perror("[-] Socket creation error\n\n");
			return -1;
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &server.sin_addr)<=0)
	{
		perror("[-] Invalid address/ Address not supported \n\n");
		return -1;
	}

	while(1)
	{
		if(connect(socket_file_descriptor, (struct sockaddr *)&server, sizeof(server)) < 0)
		{
			printf("[-] Connection Failed \n\n");
			return -1;
		}

		char message[256];
		printf("Enter Message: ");
		scanf("%s", message);

		send(socket_file_descriptor , message , strlen(message) , 0);
		printf("[+] Message Sent\n\n");

		valread = read(socket_file_descriptor, buffer, 1024);
		printf("Message from Server: %s\n", buffer);
	}

	return 0;
}
