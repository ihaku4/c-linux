#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void test()
{
  int i = 0xffffffff;
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

  printf("%x\n", EOF);
  printf("%x\n", NULL);

  return;
}

void test_perror_errno()
{
  FILE *fp = fopen("false_path", "r");
  if (fp == NULL) {
    printf("error no. from printf: %d\n", errno);
    perror("test perror");
    printf("error no. from printf: %d\n", errno);
    exit(1);
  }
}

void test_io()
{
  int c;
  unsigned char content[1000];
  FILE *fp;
  int i;

  // XXX fgetc fputc
  fp = fopen("test.file", "r");
  if (fp == NULL) perror("open file fail");
  i = 0;
  while ((c = fgetc(fp)) != EOF) {
    //content[i++] = (char) c;
    content[i++] = (unsigned char) c;
    //fputc(c, stdout);
    //putchar(c);
  }
  content[i] = 0;
  puts(content);

  c = fgetc(fp);
  printf("%x\n", c);
  //fclose(fp);


  // XXX fgets fputs
  char line_tmp[1000];
  fp = fopen("test.file", "r");
  if (fp == NULL) perror("open file fail");
  i = 0;
  while ((fgets(line_tmp, 1000, fp)) != NULL) {
    //content[i++] = (char) c;
    //fputc(c, stdout);
    //putchar(c);
    fputs(line_tmp, stdout);
    puts(line_tmp); // this guy append an additional '\n' at end. so there will be 2 '\n' if the original content ends with '\n'
  }

  // XXX read write, open close, ?...
  // unistd.h, sys/types.h sys/stat.h fcntl.h
  // Unbuffered IO
  // File Descriptor: int fd - FILE *fp
}

void main()
{
//  test();
  test_io();
}

