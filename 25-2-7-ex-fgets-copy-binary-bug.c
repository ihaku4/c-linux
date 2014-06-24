#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  FILE *fp;
  FILE *fp_dst;
  //char *ch;
  char buffer[10];
  int size = 10;

  if ( (fp = fopen("file2", "r")) == NULL) {
    perror("Open file file2\n");
    exit(1);
  }
  if ( (fp_dst = fopen("file3", "w")) == NULL) {
    perror("Open file file3\n");
    exit(1);
  }
//  while ( (ch = fgets(buffer, size, fp)) != EOF)
//    fputs(ch, fp_dst);
  while ( (fgets(buffer, size, fp)) != NULL)
    fputs(buffer, fp_dst);
  fclose(fp);
  fclose(fp_dst);
  return 0;
}
