#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{
  int fd, save_fd;
  char msg[] = "This is a test\n";
  fd = open("somefile", O_RDWR|O_CREAT, 
      S_IRUSR|S_IWUSR);
  if(fd<0) {
    perror("open");
    exit(1);
  }
  save_fd = dup(STDOUT_FILENO);
  dup2(fd, STDOUT_FILENO);
  close(fd);
  write(STDOUT_FILENO, msg, strlen(msg));
  dup2(save_fd, STDOUT_FILENO);
  write(STDOUT_FILENO, msg, strlen(msg));
  close(save_fd);
  return 0;
}
