#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netdb.h>

int main(int argc, char * argv[]) {
  struct sockaddr_in server, client;
  if (argc != 2)
    printf("Input format not correct");
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd == -1)
    printf("Error in socket();");
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(atoi(argv[1]));
  if (bind(sockfd, (struct sockaddr * ) & server, sizeof(server)) < 0)
    printf("Error in blind()! \n");
  char buffer[100];
  socklen_t server_len = sizeof(server);
  printf("Server waiting\n");
  if (recvfrom(sockfd, buffer, 100, 0, (struct sockaddr * ) & server, & server_len) < 0)
    printf("Error in recvfrom()!");
  printf("Got a datagram : %s", buffer);
  return 0;
}

/*
cseb1@sjcet-H81M-DS2:~/Joswin/udp$ gcc udp_server.c -o server
cseb1@sjcet-H81M-DS2:~/Joswin/udp$ ./server 2050
Server waiting
Got a datagram : MESSAGE
*/
