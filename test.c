#include <string.h>
#include <stdio.h>

void main()
{
  int i = 0xfffffffff;
  printf("%d", 6/7);
  printf("%d", -6/7);
  printf("\n");
  printf("%X", 0xfff7&0x7f00);
  printf("\n%d, %x", -0xffffff, 0xffff);
  printf("\n%d, %x", i, i);
  printf("\n%d", sizeof(i));

  char *saveptr;
  char line[1000] = "xxx = yyy";
  char *token;
  token = strtok_r(line, "=", &saveptr);
  printf("%s\n", token);
  token = strtok_r(NULL, "=", &saveptr);
  printf("%s\n", token);

  int t = 1234;
  void *arg = &t;
  printf("*arg = %d\n", *((int *) arg));

  printf("before convert endian: %x\n", t);
  printf("after convert endian hton: %x\n", htonl(t));
  printf("after convert endian ntoh: %x\n", ntohl(t));

  int b = 1 < 2;
  printf("%x\n", b);
  b = 1 > 2;
  printf("%x\n", b);

  return;
}
