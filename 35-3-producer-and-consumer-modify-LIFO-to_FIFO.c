#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

struct msg {
  struct msg *next;
  int num;
};

void print_list(struct msg *head);

struct msg *head;
struct msg *tail;
pthread_cond_t has_product = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *consumer(void *p)
{
  struct msg *mp;
  for (;;) {
    pthread_mutex_lock(&lock);
    while (head == NULL)
      pthread_cond_wait(&has_product, &lock);
    mp = head;
    head = mp->next;
    pthread_mutex_unlock(&lock);
    printf("Consume %d\n", mp->num);
    free(mp);
    int sec = rand() % 5;
    printf("consumer gonna sleep %d secs.\n", sec);
    sleep(sec);;
  }
}

void *producer(void *p)
{
  struct msg *mp;
  for (;;) {
    mp = malloc(sizeof(struct msg));
    mp->num = rand() % 1000 + 1;
    printf("Produce %d\n", mp->num);
    pthread_mutex_lock(&lock);

    if (tail != NULL) tail->next = mp;
    tail = mp;
    tail->next = NULL;
    if (head == NULL) head = tail;

    print_list(head);

    pthread_mutex_unlock(&lock);
    pthread_cond_signal(&has_product);
    int sec = rand() % 5;
    printf("producer gonna sleep %d secs.\n", sec);
    sleep(sec);;
  }
}

int main(int argc, char *argv[]) 
{
  pthread_t pid, cid; 
  srand(time(NULL));
  pthread_create(&pid, NULL, producer, NULL);
  pthread_create(&cid, NULL, consumer, NULL);
  pthread_join(pid, NULL);
  pthread_join(cid, NULL);
  return 0;
}

void print_list(struct msg *head)
{
  for (; head != NULL; head = head->next) {
    printf("%d->", head->num);
  }
  printf("NULL\n");
}
