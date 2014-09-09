#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
  pid_t pid;
  pid = fork();
  if (pid < 0) {
    perror("fork failed");
    exit(1);
  }
  if (pid == 0) {
    int i;
    for (i = 3; i > 0; i--) {
      printf("This is the child\n");
      sleep(1);
    }
    exit(3);
  } else {
    int stat_val;
    waitpid(pid, &stat_val, 0);
    //waitpid(pid, &stat_val, WNOWAIT);
    if (WIFEXITED(stat_val))
      printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
    else if (WIFSIGNALED(stat_val))
      printf("Child terminated abnormally, signal %d\n", WTERMSIG(stat_val));

    printf("exit code: %d, signal: %d, raw stat_val: 0x%x %d", WEXITSTATUS(stat_val), WTERMSIG(stat_val), stat_val, stat_val);
  }
  return 0;
}
