#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h> // read(), write(), close()

#define MAX 80
#define PORT 8080

// Function designed for chat between client and server.
void func(int connfd)
{
	char buffer[MAX];
	int n;
	// infinite loop for chat
	for (;;) {
		bzero(buffer, MAX);

		// read the message from client and copy it in buffer
		read(connfd, buffer, sizeof(buffer));
		// print buffer which contains the client contents
		printf("From client: %sTo client : ", buffer);
		bzero(buffer, MAX);
		n = 0;
		// copy server message in the buffer
		while ((buffer[n++] = getchar()) != '\n');

		// and send that buffer to client
		write(connfd, buffer, sizeof(buffer));

		// if msg contains "Exit" then server exit and chat ended.
		if (strncmp("exit", buffer, 4) == 0) {
			printf("Server Exit...\n");
			break;
		}
	}
}

// Driver function
int main()
{
	int sockfd, connfd, len;
	struct sockaddr_in server, client;

	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	} else
		printf("Socket successfully created..\n");

	bzero(&server, sizeof(server));

	// assign IP, PORT
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(PORT);

	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (struct sockaddr * ) & server, sizeof(server))) != 0) {
		printf("socket bind failed...\n");
		exit(0);
	} else
		printf("Socket successfully binded..\n");

	// Now server is ready to listen and verification
	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	} else
		printf("Server listening..\n");

	len = sizeof(client);

	// Accept the data packet from client and verification
	connfd = accept(sockfd, (struct sockaddr *) & client, &len);
	if (connfd < 0) {
		printf("server accept failed...\n");
		exit(0);
	} else
		printf("server accept the client...\n");

	// Function for chatting between client and server
	func(connfd);

	// After chatting close the socket
	close(sockfd);
}

/*
joswin@LAPTOP:~/TCP$ gcc server.c -o server
joswin@LAPTOP:~/TCP$ ./server
Socket successfully created..
Socket successfully binded..
Server listening..
server accept the client...
From client: Message 1
To client : Message 2
From client: Message 3
To client : exit
Server Exit...
*/
