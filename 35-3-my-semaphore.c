#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#define NUM 5

// XXX sem->count is a local operation?

//struct semaphore {
//  int count;
//  pthread_cond_t cond;
//  pthread_mutex_t mutex;
//};

typedef struct {
  int count;
  pthread_cond_t cond;
  pthread_mutex_t mutex;
} semaphore;

int sem_init(semaphore *sem, int pshared, unsigned int value);
int sem_destroy(semaphore *sem);
int sem_wait(semaphore *sem);
int sem_trywait(semaphore *sem);
int sem_post(semaphore *sem);

int sem_init(semaphore *sem, int pshared, unsigned int value)
{
  sem->count = value;
//  sem->cond = PTHREAD_COND_INITIALIZER;
//  sem->mutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_cond_init(&sem->cond, NULL);
  pthread_mutex_init(&sem->mutex, NULL);
  return 0;
}

int sem_destroy(semaphore *sem)
{
  // using pthread_cond_t pointer & free ?
  return 0;
}

int sem_wait(semaphore *sem)
{
  if (0 == sem->count)
    pthread_cond_wait(&sem->cond, &sem->mutex);
  sem->count--;
  return 0;
}

int sem_trywait(semaphore *sem)
{
  if (0 == sem->count)
    return -1; //return EAGAIN;
  else {
    sem->count--;
    return 0;
  }
}

int sem_post(semaphore *sem)
{
  sem->count++;
  return pthread_cond_signal(&sem->cond);
}

int queue[NUM];
semaphore blank_number, product_number;

void *producer(void *arg) 
{
  int p = 0;
  while (1) {
    sem_wait(&blank_number);
    queue[p] = rand() % 1000 + 1;
    printf("Produce %d\n", queue[p]);
    sem_post(&product_number);
    p = (p+1)%NUM;
    sleep(rand()%5);
  }
}

void *consumer(void *arg) 
{
  int c = 0;
  while (1) {
    sem_wait(&product_number);
    printf("Consume %d\n", queue[c]);
    queue[c] = 0;
    sem_post(&blank_number);
    c = (c+1)%NUM;
    sleep(rand()%5);
  }
}

int main(int argc, char *argv[]) 
{
  pthread_t pid, cid; 
  sem_init(&blank_number, 0, NUM);
  sem_init(&product_number, 0, 0);
  pthread_create(&pid, NULL, producer, NULL);
  pthread_create(&cid, NULL, consumer, NULL);
  pthread_join(pid, NULL);
  pthread_join(cid, NULL);
  sem_destroy(&blank_number);
  sem_destroy(&product_number);
  return 0;
}
