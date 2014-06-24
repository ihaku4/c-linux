#include <stdlib.h>
#include <stdio.h>

int main(void)
{
  FILE *fp = NULL;
  //fp = fopen("/etc/shadow", "r");
  //fp = fopen("23-3-array.c", "r");
  //fp = fopen("makefile-test", "r+");
  //fp = fopen("makefile-te-FAKE_NAME", "r");
  printf("opening file####.\n");
  fp = fopen("/", "r");
  if (fp == NULL) {
    perror("Open /etc/shadow");
    exit(1);
  }
  return 0;
}
