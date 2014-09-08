#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void test_func();

int main(void)
{
  FILE *fp;
  int ch;
  int is_loop = 0;

  test_func();

  if ( (fp = fopen("mock_log_file.log", "a")) == NULL) {
    perror("Open file mock_log_file.log\n");
    exit(1);
  }

  while (is_loop) {
    sleep(1);
    time_t t = time(NULL);
    struct tm *local_time = localtime(&t);
    char *t_str = asctime(local_time);
    //char *t_str = asctime(localtime(&t));
    //char *t_str = asctime(localtime(&(time(NULL)))); // this not work.
    //fputs( t_str, fp);
    fputs( t_str, stdout);
    fflush(NULL);
  }
  fclose(fp);
  return 0;
}

void test_func() {
  printf("\n%d", sizeof(struct tm));
  printf("\n%d", sizeof(time_t));
  time_t t = time(NULL);
  print_struct_tm(&t);
}

void print_struct_tm(const struct tm *time) {
  printf("tm_sec: %x\n", time->tm_sec);
  printf("tm_min: %x\n", time->tm_min);
  printf("tm_hour: %x\n", time->tm_hour);
  printf("tm_mday: %x\n", time->tm_mday);
  printf("tm_mon: %x\n", time->tm_mon);
  printf("tm_year: %x\n", time->tm_year);
  printf("tm_wday: %x\n", time->tm_wday);
  printf("tm_yday: %x\n", time->tm_yday);
  printf("tm_isdst: %x\n", time->tm_isdst);
}

//struct tm {
//  int tm_sec;         /* seconds */
//  int tm_min;         /* minutes */
//  int tm_hour;        /* hours */
//  int tm_mday;        /* day of the month */
//  int tm_mon;         /* month */
//  int tm_year;        /* year */
//  int tm_wday;        /* day of the week */
//  int tm_yday;        /* day in the year */
//  int tm_isdst;       /* daylight saving time */
//};
//
