#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  FILE *fp;

  if ( (fp = fopen("file2", "r+")) == NULL) {
    perror("Open file file2\n");
    exit(1);
  }
  //while ( (ch = getchar()) != EOF)
  //  fputc(ch, fp);
  //rewind(fp);
  //while ( (ch = fgetc(fp)) != EOF)
  //  putchar(ch);
  if (fseek(fp, 100, SEEK_SET) != 0) {
    perror("Seek file file2");
    exit(1);
  }
  fputc('K', fp);
  fclose(fp);
  return 0;
}
