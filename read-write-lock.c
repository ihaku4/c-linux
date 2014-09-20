#include <stdio.h>
#include <pthread.h>

pthread_rwlock_t rwlock;
pthread_t thr_r;
pthread_t thr_r_2;
pthread_t thr_w;

void *thr_fn_w(void *arg)
{
  pthread_rwlock_wrlock(&rwlock);
  puts("write locked.\n");
  return NULL;
}

void *thr_fn_r(void *arg)
{
  pthread_rwlock_rdlock(&rwlock);
  puts("read locked.\n");
  return NULL;
}

int main(void)
{
  puts("creating read thread.\n");
  pthread_create(&thr_r, NULL, thr_fn_r, NULL);
  pthread_create(&thr_r_2, NULL, thr_fn_r, NULL);
  puts("creating write thread.\n");
  sleep(1);
  pthread_create(&thr_w, NULL, thr_fn_w, NULL);
  pthread_join(thr_r, NULL);
  pthread_join(thr_r_2, NULL);
  pthread_join(thr_w, NULL);
  return 0;
}
