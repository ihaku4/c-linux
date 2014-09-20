#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM 5

// philosophers and chopsticks, 
// chopsticks[0] is in the left side of philosophers[0] and,
// chopsticks[1] is in the right side of philosophers[0]. 
pthread_t philosophers[NUM];
pthread_mutex_t chopsticks[NUM];
int chopstick_status[NUM];

void *a_philosopher_s_life(void *arg)
{
  int index = *((int *) arg);
  int index_next = index == NUM - 1 ? 0 : index + 1;
  pthread_mutex_t *chopstick_l = chopsticks + index;
  pthread_mutex_t *chopstick_r = chopsticks + index_next;
  int i;

  while (1) {
    printf("chopstick status: \n");
    for (i = 0; i < NUM; i++) {
      printf("\t%d : %d\n", i, chopstick_status[i]);
    }

    // thinking
    usleep(rand()%10);
    // prepare eating
      // left chopstick
      pthread_mutex_lock(chopstick_l);
      chopstick_status[index] = index;
      printf("Philosopher %d fetches chopstick %d\n", index, index);
      // right chopstick
      pthread_mutex_lock(chopstick_r);
      chopstick_status[index_next] = index;
      printf("Philosopher %d fetches chopstick %d\n", index, index_next);
    // eating
    usleep(rand()%10);
    // finish eating
    pthread_mutex_unlock(chopstick_l);
    chopstick_status[index] = -1;
    pthread_mutex_unlock(chopstick_r);
    chopstick_status[index_next] = -1;
    printf("Philosopher %d releases chopstick %d %d\n", index, index, index_next);
  }
}

int main(void)
{
  int i;
  int index[NUM];

  for (i = 0; i < NUM; i++) {
    index[i] = i;
    chopstick_status[i] = -1;
    pthread_create(philosophers+i, NULL, a_philosopher_s_life, index+i);
  }
  for (i = 0; i < NUM; i++) {
    pthread_join(*(philosophers+i), NULL);
  }
  return 0;
}

//int main(void)
//{
//  int i;
//  int index[NUM];
//  for (i = 0; i < NUM; i++) {
//    printf("------- %d\n", i);
//    index[i] = i;
//    sleep(1);
//    pthread_create(philosophers+i, NULL, a_philosopher_s_life, &i);
//    //pthread_create(philosophers+i, NULL, a_philosopher_s_life, index+i);
//  }
//  for (i = 0; i < NUM; i++) {
//    pthread_join(*(philosophers+i), NULL);
//  }
//  return 0;
//}
