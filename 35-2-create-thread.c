#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

pthread_t ntid;

void printids(const char *s)
{
  pid_t pid;
  pthread_t tid;
  pid = getpid();
  tid = pthread_self();
  printf("%s pid %u tid %u (0x%x)\n", s, (unsigned int) pid, (unsigned int) tid, (unsigned int) tid);
  printf("%s child thread id: %u\n",s, (unsigned int) ntid);
}

void *thr_fn(void *arg)
{
  printids(arg);
  return NULL;
}

int main(void)
{
  int err;
  if (0 != (err = pthread_create(&ntid, NULL, thr_fn, "new thread: "))) {
    fprintf(stderr, "can't create thread: %s\n", strerror(err));
    exit(1);
  }
  printids("main thread:");
  sleep(1);

  return 0;
}
