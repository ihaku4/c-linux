#include <stdio.h>
#include <unistd.h>

int main(void)
{
  int counter;
  alarm(8);
  for (counter = 0; 1; counter++) {
    printf("counter = %d\n", counter);
    if (90002 == counter) {
      printf("\nalarm remain: %d\n", alarm(2));
      exit(1);
    }
  }
  return 0;
}
