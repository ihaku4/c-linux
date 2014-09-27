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

config_info get_config();
void Listen(config_info config);
int Accept(int listenfd);
void get_request_path(char *http_head, char *path);
void response(char *file_path, int connfd);

int main(void)
{
  int connfd;
  pid_t pid;

  // listen ...

  while ((connfd = Accept(listenfd)) != 0) {
    pid = fork();
    if (0 != pid) { // error handling.
      close(connfd);
      continue;
    } else {
                    // close(listenfd);
      // read from client
      get_request_path
      response  // this function handles files and CGIs
                    // close(connfd);
        }
    }
}
