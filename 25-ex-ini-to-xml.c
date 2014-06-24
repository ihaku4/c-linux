#include <stdio.h>
#include <stdlib.h>

#define FILE_LENGHTH 1000

int main(void)
{
  FILE *fp;
  int ch;
  
  char str[FILE_LENGHTH];
  int i;
  memset(str, 0, sizeof(char)*FILE_LENGHTH);

  if ( (fp = fopen("file.ini", "r")) == NULL) {
    perror("Open file mock_log_file.log\n");
    exit(1);
  }

  i = 0;
  while ((ch = fgetc(fp)) != EOF) {
    //fputc(ch, stdout);
    str[i++] = (char) ch;
    if (i >= FILE_LENGHTH) break;
  }
  fclose(fp);

  printf("file read : \n\n%s\n\ncharacter count: %d", str, i);

  char *line = strtok(str, "\n");
  printf("%s\n ========= \n", line);
  while ((line = strtok(NULL, "\n")) != NULL)
    printf("%s\n ========= \n", line);
  return 0;
}
