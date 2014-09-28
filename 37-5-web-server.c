#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include "wrap.h"

//#define MAXLINE 80
#define SERV_PORT 8000
/*
 * read config file
 * listen & accept
 * parse request path ;"\r\n"
 *   read html file & write out ;default index.html
 *   exec CGI & dup2 & write out
 */

#define MAXLINE 1000

//struct config {
//  uint16_t port;
//  char server_path[MAXLINE];
//}
typedef struct {
  uint16_t port;
  char server_path[MAXLINE];
} config_info;

//config_info get_config();
//void Listen(config_info config);
//int Accept(int listenfd);
//void get_request_path(char *http_head, char *path);
//void response(char *file_path, int connfd);
//void start_server();
//
//config_info get_config()
//{
//    config_info ci;
//    ci.port = 8000;
//    server_path = "./httpd.ini"; // is this char retain after return?
//}

void sig_chld(int signo) 
{
  int status;
  int pid;
  pid = wait(&status);
  printf("child finished: pid = %d, status = %x, exit status = %d\n", pid, status, WEXITSTATUS(status));
  fflush(stdout);
}

//void start_server()
//{
//  int connfd;
//  pid_t pid;
//
//  // listen ...
//
//  while ((connfd = Accept(listenfd)) != 0) {
//    pid = fork();
//    if (0 != pid) { // error handling.
//      close(connfd);
//      continue;
//    } else {
//                    // close(listenfd);
//      // read from client
//      get_request_path
//      response  // this function handles files and CGIs
//                    // close(connfd);
//    }
//  }
//}

int main(void)
{
  struct sockaddr_in servaddr, cliaddr;
  socklen_t cliaddr_len;
  int listenfd, connfd;
  char buf[MAXLINE];
  char str[INET_ADDRSTRLEN];
  int i, n, c, len;
  pid_t pid;
  struct sigaction newact, oldact;
  char *key_saveptr;
  char *path;
  char html_content[MAXLINE];
  FILE *fp;
  char web_root[MAXLINE] = ".";
  char response_head[MAXLINE] = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
  listenfd = Socket(AF_INET, SOCK_STREAM, 0);

  // allow creating socket fd with same port but different ip.
  int opt = 1;
  setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

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
      n = Read(connfd, buf, MAXLINE);
      if (0 == n) {
        printf("the other side has been closed.\n");
        exit(1);
      }
      printf("\n----------------------");
      printf("received from %s at PORT %d\n",
          inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),
          ntohs(cliaddr.sin_port));

      printf("client request: \n%s\n", buf);

      path = strtok_r(buf, " ", &key_saveptr);
      path = strtok_r(NULL, " ", &key_saveptr); // after split space, the 2ed should be path.
      if (path[0] != '/') {
        len = strlen(web_root);
        web_root[len] = '/';
        web_root[len+1] = 0;
      }
      len = strlen(web_root);
      memcpy(web_root+len, path, strlen(path)+1);

      printf("request file: %s\n", web_root);
      fp = fopen(web_root, "r");
      if (fp == NULL) {
        perror("open file fail");
        exit(1);
      }
      i = 0;
      while ((c = fgetc(fp)) != EOF) {
        html_content[i++] = (unsigned char) c;
      }

      Write(connfd, response_head, strlen(response_head));
      Write(connfd, html_content, i);
      Close(connfd);
      exit(0);
    }
  }

  return 0;
}
