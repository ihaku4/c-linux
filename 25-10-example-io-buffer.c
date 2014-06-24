#include <stdio.h>

int main(void)
{
  printf("hello world");
  printf("test..");
  //fflush(stdout);
  fflush(NULL);
  while(1);
  return 0;
}
