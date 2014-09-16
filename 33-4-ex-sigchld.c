#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

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
  int pid;
  struct sigaction newact, oldact;

  if ((pid = fork()) < 0) {
    perror("fork");
    exit(1);
  }
  if (pid > 0) {
    printf("this is parent.\n");
    fflush(stdout);
    newact.sa_handler = sig_chld;
    sigemptyset(&newact.sa_mask);
    newact.sa_flags = 0;
    sigaction(SIGCHLD, &newact, &oldact);
    pause();
  } else if (0 == pid) {
    printf("this is child.\n");
    fflush(stdout);
    sleep(1);
    exit(2);
  }
  return 0;
}
