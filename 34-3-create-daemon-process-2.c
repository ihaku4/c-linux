#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

void daemonize(void)
{
  pid_t pid;

  /* fork */
  if ((pid = fork()) < 0) {
    perror("fork");
    exit(1);
  } else if (pid != 0)
    exit(0);
  /* setsid */
  if (setsid() < 0) {
    perror("create session");
    exit(1);
  }
  /* chdir */
  if (chdir("/") < 0) {
    perror("chdir");
    exit(1);
  }
  /* TODO  ( Is this necessary? ) attach file descriptor to /dev/null */
  close(0);
  open("/dev/null", O_RDWR);
  dup2(0, 1);
  dup2(0, 2);
}

int main(void)
{
  daemonize();
  while (1);
}
