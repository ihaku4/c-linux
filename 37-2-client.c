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

  sockfd = Socket(AF_INET, SOCK_STREAM, 0);

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
  servaddr.sin_port = htons(SERV_PORT);

  Connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

  while (NULL != fgets(buf, MAXLINE, stdin)) {
    Write(sockfd, buf, strlen(buf));
    n = Read(sockfd, buf, MAXLINE);
    if (0 == n)
      printf("the other side has been closed.\n");
    else
      Write(STDOUT_FILENO, buf, n);
  }

  Close(sockfd);
  return 0;
}
