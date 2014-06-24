#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int const MEM_SIZE = 100;
  int total_size = 0;
  while (1) {
    int *p = malloc(sizeof(int));
    if (p == NULL) {
      printf("out of memory\n");
      printf("total allocated memory: %d\n", total_size);
      break;
    }
    total_size += sizeof(int);
  }
}
