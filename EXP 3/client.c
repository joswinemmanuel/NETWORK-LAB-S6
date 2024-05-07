#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

void func(int sockfd) {
	char buffer[80];
	int n;
	for (;;) {

		bzero(buffer, sizeof(buffer));
		printf("To Server : ");
		n = 0;
		while ((buffer[n++] = getchar()) != '\n');
		write(sockfd, buffer, sizeof(buffer));

		bzero(buffer, sizeof(buffer));
		read(sockfd, buffer, sizeof(buffer));
		printf("From Server : %s", buffer);

		if ((strncmp(buffer, "exit", 4)) == 0) {
			printf("Client Exit...\n");
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
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(8080);

	if (connect(sockfd, (struct sockaddr * ) & server, sizeof(server)) != 0) {
		printf("connection with the server failed...\n");
		exit(0);
	} else
		printf("connected to the server..\n");

	func(sockfd);
	close(sockfd);
}

/*
joswin@LAPTOP:~/TCP$ gcc client.c -o client
joswin@LAPTOP:~/TCP$ ./client 
Socket successfully created..
connected to the server..
Enter the string : Message 1
From Server : Message 2
Enter the string : Message 3
From Server : exit
Client Exit...
*/
