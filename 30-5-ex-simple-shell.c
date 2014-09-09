#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define MAXLINE 1000

// command structure: 
// cmd arguments, < >, |

int is_blank(char c);
char * trim(char *s);
void exec_cmd(char *line);

int is_blank(char c) {
  return c == 0xA || c == 0x20;
}

void exec_cmd(char *line) {
  char *cmd;
  char * arguments[100];
  char out_redirect[MAXLINE];
  char in_redirect[MAXLINE];
  int i;
  char *pos;
  int fd;
  memset(out_redirect, 0, MAXLINE);
  memset(in_redirect, 0, MAXLINE);

  cmd = trim(line);
  
  //printf("\n%s\n", cmd);

  // pipe TODO

  // in redirect
  pos = strchr(cmd, '<');
  if (pos != NULL) {
    *pos = ' ';
    for (pos++; is_blank(*pos) && *pos != '\0'; pos++);
    for (i = 0; !is_blank(*pos) && *pos != '\0'; pos++, i++) {
      in_redirect[i] = *pos;
      *pos = ' ';
    }
    if (strlen(in_redirect) > 0) {
      fd = open(in_redirect, O_RDONLY);
      if (fd < 0) {
        perror("open");
        exit(1);
      }
      dup2(fd, STDIN_FILENO);
      close(fd);
    }
  }

  // out redirect
  pos = strchr(cmd, '>');
  if (pos != NULL) {
    *pos = ' ';
    for (pos++; is_blank(*pos) && *pos != '\0'; pos++);
    for (i = 0; !is_blank(*pos) && *pos != '\0'; pos++, i++) {
      out_redirect[i] = *pos;
      *pos = ' ';
    }
    if (strlen(out_redirect) > 0) {
      fd = open(out_redirect, O_WRONLY);
      if (fd < 0) {
        perror("open");
        exit(1);
      }
      dup2(fd, STDOUT_FILENO);
      close(fd);
    }
  }

  // arguments
  arguments[0] = strtok(cmd, " ");
  for (i = 1; (arguments[i] = strtok(NULL, " ")) != NULL; i++);

  // run
  execvp(arguments[0], arguments);
  perror("exec error");
}

char * trim(char *s)
{
  int n;
  int i;
  for (; is_blank(*s); s++);
  n = strlen(s);
  for (i = n-1; is_blank(s[i]) && i >= 0; i--) {
    s[i] = 0x0;
  }
  return s;
}

int main(void)
{
  char *promote_symbol = "my@ruff shell > ";
  char line[MAXLINE];
  char *subline;
  char *subline2;
  int n;
  pid_t pid;
  pid_t pid2;
  int fd[2];
  int fd2[2];
  int fd_inter_sub[2];

    while (1) {
      memset(line, 0, MAXLINE);
      fputs("my@ruff shell > ", stdout);
      fflush(stdout);
      n = read(STDIN_FILENO, line, MAXLINE-1);
      line[n] = '\0';
      
      // pipe
      subline = strtok(line, "|");
      subline2 = strtok(NULL, "|");

      if (pipe(fd) < 0) {
        perror("pipe");
        exit(1);
      }
      if (subline2 != NULL) {
        if (pipe(fd2) < 0) {
          perror("pipe");
          exit(1);
        }
        if (pipe(fd_inter_sub) < 0) {
         perror("pipe");
         exit(1);
        }
      }

      pid = fork();
      if (pid < 0) {
        perror("fork");
        exit(1);
      }
      if (pid > 0) {
        close(fd[0]);
        write(fd[1], subline, strlen(subline));
        int stat_val;
        waitpid(pid, &stat_val, 0);
      } else {
        close(fd[1]);
        n = read(fd[0], subline, MAXLINE-1);
        subline[n] = '\0';
        if (subline2 != NULL) {
          close(fd_inter_sub[0]);
          dup2(fd_inter_sub[1], STDOUT_FILENO);
        }
        exec_cmd(subline);
        exit(0);
      }

      if (subline2 != NULL) {
        pid2 = fork();
        if (pid2 < 0) {
          perror("fork");
          exit(1);
        }
        if (pid2 > 0) {
          close(fd2[0]);
          close(fd_inter_sub[0]);
          close(fd_inter_sub[1]);
          write(fd2[1], subline2, strlen(subline2));
          int stat_val;
          waitpid(pid2, &stat_val, 0);
        } else {
          close(fd2[1]);
          close(fd_inter_sub[1]);
          n = read(fd2[0], subline2, MAXLINE-1);
          subline2[n] = '\0';
          dup2(fd_inter_sub[0], STDIN_FILENO);
          exec_cmd(subline2);
          exit(0);
        }
      }
      
    }
    

  // promote symbol
  // cmd recognize, and "exec"
  // redirectory < >
  // pipe |
  // string parse: | < > \s 
}
