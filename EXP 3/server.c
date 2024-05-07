#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>

void func(int connfd) {
	char buffer[80];
	int n;
	for (;;) {
		
		bzero(buffer, sizeof(buffer));
		read(connfd, buffer, sizeof(buffer));
		printf("From Client: %s", buffer);

		bzero(buffer, sizeof(buffer));
		printf("To Client: ");
		n = 0;
		while ((buffer[n++] = getchar()) != '\n');
		write(connfd, buffer, sizeof(buffer));

		if (strncmp(buffer, "exit", 4) == 0) {
			printf("Server Exit...\n");
			break;
		}
	}
}

int main() {
	struct sockaddr_in server, client;

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	} else
		printf("Socket successfully created..\n");

	bzero(&server, sizeof(server));

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(8080);

	if (bind(sockfd, (struct sockaddr * ) & server, sizeof(server)) < 0) {
		printf("socket bind failed...\n");
		exit(0);
	} else
		printf("Socket successfully binded..\n");

	if (listen(sockfd, 5) < 0) {
		printf("Listen failed...\n");
		exit(0);
	} else
		printf("Server listening..\n");

	int len = sizeof(client);

	int connfd = accept(sockfd, (struct sockaddr *) & client, & len);

	if (connfd < 0) {
		printf("server accept failed...\n");
		exit(0);
	} else
		printf("server accept the client...\n");

	func(connfd);

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
