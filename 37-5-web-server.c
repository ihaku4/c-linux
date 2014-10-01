#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <signal.h>
#include "wrap.h"

//#define MAXLINE 80
#define SERV_PORT 8000
#define MAXLINE 1000

/*
 * read config file
 * listen & accept
 * parse request path ;"\r\n"
 *   read html file & write out ;default index.html
 *   exec CGI & dup2 & write out
 */

/*
 * TODO detect file type
 *
 */

/* 
//struct config {
//  uint16_t port;
//  char server_path[MAXLINE];
//}
*/
typedef struct {
  uint16_t port;
  char server_path[MAXLINE];
} config_info;

void get_target_path(char *request_head, char *dest);
void handle_request(int connfd);
void sig_chld(int signo);
void get_file_type(const char *path, char *filetype);
int is_file_executable(const char *path);
void response(int connfd, const char *target_path);

/* 
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
*/

int main(void)
{
  struct sockaddr_in servaddr, cliaddr;
  socklen_t cliaddr_len;
  int listenfd, connfd;
  pid_t pid;
  struct sigaction newact, oldact;
  char str[INET_ADDRSTRLEN];

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
    printf("\n----------------------");
    printf("received from %s at PORT %d\n",
        inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),
        ntohs(cliaddr.sin_port));

    pid = fork();
    if (pid != 0) {
      Close(connfd);

      newact.sa_handler = sig_chld;
      sigemptyset(&newact.sa_mask);
      newact.sa_flags = 0;
      sigaction(SIGCHLD, &newact, &oldact);
      continue;
    } else {
      Close(listenfd);
      handle_request(connfd);
      Close(connfd);
      exit(0);
    }
  }
  return 0;
}

void sig_chld(int signo) 
{
  int status;
  int pid;
  pid = wait(&status);
  printf("child finished: pid = %d, status = %x, exit status = %d\n", pid, status, WEXITSTATUS(status));
  fflush(stdout);
}

/* 
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
*/

void get_file_type(const char *path, char *filetype)
{
  // TODO
}

int is_file_executable(const char *path)
{
  struct stat buf;

  stat(path, &buf);
  // S_IXUSR(0100) seems not enough. S_IXGRP S_IXOTH
  return buf.st_mode & 0111;
    
}

void get_target_path(char *request_head, char *dest)
{
  char index[MAXLINE] = "/index.html";
  char *path;
  char *key_saveptr;
  int len;

  path = strtok_r(request_head, " ", &key_saveptr);
  path = strtok_r(NULL, " ", &key_saveptr); // after split space, the 2ed should be path.
  if (path[0] != '/') {
    len = strlen(dest);
    dest[len] = '/';
    dest[len+1] = 0;
  }
  len = strlen(dest);
  if (strcmp(path, "/") == 0) {
    memcpy(dest+len, index, strlen(index)+1);
  } else {
    memcpy(dest+len, path, strlen(path)+1);
  }

  printf("\n----------------------");
  printf("request file: %s\n", dest);
}

void response(int connfd, const char *target_path)
{
  int i, c;
  char html_content[MAXLINE];
  char filetype[MAXLINE];
  char RESPONSE_HEAD_TEMPLATE[MAXLINE] = "HTTP/1.1 200 OK\r\nContent-Type: %s\r\n\r\n";
  char RESPONSE_HEAD_TEMPLATE_404[MAXLINE] = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<html><body>request file not found</body></html>";
  char response_head[MAXLINE];
  FILE *fp;

  // locate target file
  fp = fopen(target_path, "r");
  if (fp == NULL) {
    perror("open file fail");
    //exit(1);
    Write(connfd, RESPONSE_HEAD_TEMPLATE_404, strlen(RESPONSE_HEAD_TEMPLATE_404));
    return;
  }

  // response header
    // 404 200 
    // detect file type, and whether CGI
  get_file_type(target_path, filetype);
  //sprintf(response_head, RESPONSE_HEAD_TEMPLATE, filetype);
  sprintf(response_head, RESPONSE_HEAD_TEMPLATE, "text/plain");
  Write(connfd, response_head, strlen(response_head));

  // response body
  if (is_file_executable(target_path)) {
    dup2(connfd, STDOUT_FILENO);
    execl(target_path, NULL);
    return;
  } else {
    i = 0;
    while ((c = fgetc(fp)) != EOF) {
      html_content[i++] = (unsigned char) c;
    }
    Write(connfd, html_content, i);
  }
}

void handle_request(int connfd)
{
  int n;
  char buf[MAXLINE];
  char target_path[MAXLINE] = "./var/www";

  // read request
  n = Read(connfd, buf, MAXLINE);
  if (0 == n) {
    printf("the other side has been closed.\n");
    exit(1);
  }
  buf[n] = 0;
  printf("client request: \n%s\n", buf);

  // parse request and get request path
  get_target_path(buf, target_path);

  // response
  response(connfd, target_path);

  Close(connfd);
}
