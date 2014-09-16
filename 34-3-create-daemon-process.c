#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  pid_t pid;
  if (-1 == (pid = setsid())) {
    fputs("create session fail", stderr);
    exit(1);
  }
  while (1);
  return pid;
}
