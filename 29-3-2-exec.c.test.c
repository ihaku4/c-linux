#include <unistd.h>
#include <stdlib.h>
int main(void)
{
  //char *line = "ps";
  char *line = "ls";
  //execlp("ps", "ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL);
  //execlp(line, line, "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL);
  execlp(line, line, NULL);
  perror("exec ps");
  exit(1);
}
