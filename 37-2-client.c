/* client.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "wrap.h"

#define MAXLINE 80
#define SERV_PORT 8000

int main(int argc, char *argv[])
{
  struct sockaddr_in servaddr;
  char buf[MAXLINE];
  int sockfd, n;
  char *str;

  if (argc != 2) {
    perr_exit("usage: ./client message\n");
  }
  str = argv[1];

  sockfd = Socket(AF_INET, SOCK_STREAM, 0);

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
  servaddr.sin_port = htons(SERV_PORT);

  Connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

  Write(sockfd, str, strlen(str));

  n = Read(sockfd, buf, MAXLINE);
  printf("Response from server:\n");
  Write(STDOUT_FILENO, buf, n);

  close(sockfd);
  return 0;
}
