#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "stringutil.h"
#include "stringutil.c"
#define MAXLINE 1000

// command structure: 
// cmd arguments, < >, |

void exec_cmd(char *line);
int run_if_builtin(const char *cmd[]);
void parse_command(char *line, char *arguments[]);
int exec_if_builtin_cmd(char *line);

int exec_if_builtin_cmd(char *line)
{
  char *arguments[100];
  parse_command(line, arguments);
  return run_if_builtin(arguments); 
}

void exec_cmd(char *line) 
{
  char *arguments[100];
  redirect_io(line);
  parse_command(line, arguments);
  execvp(arguments[0], arguments);
  perror("exec error");
}

void redirect_io(char *line)
{
  char *cmd;
  char out_redirect[MAXLINE];
  char in_redirect[MAXLINE];
  int i;
  char *pos;
  int fd;

  memset(out_redirect, 0, MAXLINE);
  memset(in_redirect, 0, MAXLINE);
  cmd = trim(line);
  
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
}

void parse_command(char *line, char *arguments[])
{
  int i;
  char *cmd;
  cmd = trim(line);

  arguments[0] = strtok(cmd, " ");
  i = 1;
  while ((arguments[i] = strtok(NULL, " ")) != NULL) i++;
  return arguments;
}

int run_if_builtin(const char *cmd[])
{
  int res;
  if (strcmp(cmd[0], "cd") == 0) {
    if (res = chdir(cmd[1]) != 0)
      perror("change directory fail.");
    return 1;
  }
  return 0;
}


int main(void)
{
  const char *promote_symbol = "my@ruff shell > ";
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
    fputs(promote_symbol, stdout);
    fflush(stdout);
    n = read(STDIN_FILENO, line, MAXLINE-1);
    line[n] = '\0';

    // if builtin command, call and return.
    char line_cp[MAXLINE];
    memcpy(line_cp, line, n+1);
    if (exec_if_builtin_cmd(line_cp))
      continue;

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
