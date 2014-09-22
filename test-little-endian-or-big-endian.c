#include <stdio.h>

int main(void)
{
  int t = 0x34ffff33;
  char *p = &t;
  char c = *p;
  printf("%x\n", t);
  printf("%c\n", *p);
  printf("%c\n", c);
  printf("%x\n", c);
  return 0;
}

