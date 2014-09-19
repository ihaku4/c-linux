#include <pthread.h>
#include <stdio.h>

int main(void)
{
  pthread_cond_t cond;

  pthread_cond_init(&cond, NULL);
  pthread_cond_destroy(&cond);
  printf("size of pthread_cond_t: %d\n", sizeof(cond));
  printf("size of pthread_cond_t: %d\n", sizeof(pthread_cond_t));
  printf("size of int: %d\n", sizeof(int));
  return 0;
}
