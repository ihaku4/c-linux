#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NLOOP 5000

int counter; /* incremented by threads */
void *doit(void *);

int main(int argc, char **argv)
{
  pthread_t tidA, tidB;
  pthread_create(&tidA, NULL, &doit, NULL);
  pthread_create(&tidB, NULL, &doit, NULL);
  /* wait for both threads to terminate */
  pthread_join(tidA, NULL);
  pthread_join(tidB, NULL);
  return 0;
}

void *doit(void *vptr)
{
  int i, val;
  /*
   * Each thread fetches, prints, and increments the counter NLOOP times.
   * The value of the counter should increase monotonically.
   */
  for (i = 0; i < NLOOP; i++) {
    val = counter;
   // printf("%x: %d\n", (unsigned int)pthread_self(), val + 1);
    fprintf(stderr, "%x: %d\n", (unsigned int)pthread_self(), val + 1);
    counter = val + 1;
  }
  printf("%x: %d\n", (unsigned int)pthread_self(), val + 1);
  return NULL;
}
