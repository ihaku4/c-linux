#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
  FILE *fp;
  int ch;

  if ( (fp = fopen("mock_log_file.log", "a")) == NULL) {
    perror("Open file mock_log_file.log\n");
    exit(1);
  }

  while (1) {
    sleep(1);
    time_t t = time(NULL);
    char *t_str = asctime(localtime(&t));
    //char *t_str = asctime(localtime(&(time(NULL))));
    fputs( t_str, fp);
    fflush(NULL);
  }
  fclose(fp);
  return 0;
}
