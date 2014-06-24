#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  FILE *fp;
  int ch;

  if ( (fp = fopen("file2", "w+")) == NULL) {
    perror("Open file file2\n");
    exit(1);
  }
  while ( (ch = getchar()) != EOF)
    fputc(ch, fp);
  rewind(fp);
  while ( (ch = fgetc(fp)) != EOF)
    putchar(ch);
  fclose(fp);
  return 0;
}
