#include <semaphore.h>
#include <stdio.h>

void thr_sem_post(sem_t *sem)
{
//  printf("%d---", sem_post(sem));
//  fflush(stdout);
//  printf("%d---", sem_post(sem));
//  fflush(stdout);
//  printf("%d---", sem_post(sem));
//  fflush(stdout);
//  printf("%d---", sem_post(sem));
//  fflush(stdout);
}

int main(void)
{
  sem_t sem;

  pthread_t pid;
  pthread_create(&pid, NULL, thr_sem_post, &sem);

  sem_init(&sem, 0, 2);

  printf("%d", sem_wait(&sem));
  fflush(stdout);
  printf("%d", sem_wait(&sem));
  fflush(stdout);
  printf("%d", sem_trywait(&sem));
  fflush(stdout);
  printf("%d", sem_wait(&sem));
  fflush(stdout);
  printf("%d", sem_trywait(&sem));
  fflush(stdout);
  printf("%d", sem_trywait(&sem));
  fflush(stdout);
  printf("%d", sem_trywait(&sem));
  fflush(stdout);
  printf("%d", sem_trywait(&sem));
  fflush(stdout);
  printf("%d", sem_trywait(&sem));
  fflush(stdout);

  printf("%d", sem_post(&sem));
  fflush(stdout);
  printf("%d", sem_post(&sem));
  fflush(stdout);
  printf("%d", sem_post(&sem));
  fflush(stdout);
  printf("%d", sem_post(&sem));
  fflush(stdout);

  pthread_join(pid, NULL);

  sem_destroy(&sem);
}
