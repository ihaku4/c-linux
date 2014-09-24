/* server.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include "wrap.h"

#define MAXLINE 80
#define SERV_PORT 8000

void sig_chld(int signo) 
{
  int status;
  int pid;
  pid = wait(&status);
  printf("child finished: pid = %d, status = %x, exit status = %d\n", pid, status, WEXITSTATUS(status));
  fflush(stdout);
}

int main(void)
{
  struct sockaddr_in servaddr, cliaddr;
  socklen_t cliaddr_len;
  int listenfd, connfd;
  char buf[MAXLINE];
  char str[INET_ADDRSTRLEN];
  int i, n;
  pid_t pid;
  struct sigaction newact, oldact;

  listenfd = Socket(AF_INET, SOCK_STREAM, 0);

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(SERV_PORT);

  Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

  Listen(listenfd, 20);

  printf("Accepting connections ...\n");
  while (1) {
    cliaddr_len = sizeof(cliaddr);
    connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);

    pid = fork();
    if (pid != 0) {
      // XXX close connfd ?
      Close(connfd);
      // XXX handle SIGCHLD
      // XXX call wait -> clear zombie
      newact.sa_handler = sig_chld;
      sigemptyset(&newact.sa_mask);
      newact.sa_flags = 0;
      sigaction(SIGCHLD, &newact, &oldact);
      //pause();
      continue;
    } else {
      // XXX close listenfd ?
      Close(listenfd);
      while (1) {
        n = Read(connfd, buf, MAXLINE);
        if (0 == n) {
          printf("the other side has been closed.\n");
          break;
        }
        printf("received from %s at PORT %d\n",
            inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),
            ntohs(cliaddr.sin_port));

        for (i = 0; i < n; i++)
          buf[i] = toupper(buf[i]);
        Write(connfd, buf, n);
      }
      Close(connfd);
    }
  }

  return 0;
}
