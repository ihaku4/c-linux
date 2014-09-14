#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>
#define NMATCH 2

int main(void)
{
  
  regex_t *preg;
  regmatch_t pmatch[NMATCH];
  const char *text = "jfdslfjtttsfiiidjtttdsdiiiilj";
  const char *number_str = "0123456789";
  const char *re_template = "t(t)t";
  preg = malloc(sizeof(preg));
  //if (regcomp(preg, "ttt", REG_EXTENDED|REG_ICASE) == 0) {
  //if (regcomp(preg, re_template, REG_EXTENDED|REG_ICASE|REG_NOSUB) != 0) {
  if (regcomp(preg, re_template, REG_EXTENDED|REG_ICASE) != 0) {
    fputs("regcomp fail", stderr);
    exit(1);
  }
  if (regexec(preg, text, NMATCH, pmatch, REG_NOTBOL|REG_NOTEOL) != 0) {
    fputs("regexec fail", stderr);
    exit(1);
  }
  //regexec(preg, text, NMATCH, pmatch, REG_NOTBOL);
  printf("\n%s\n%s\n%s\nstart: %d, end: %d\n", re_template, text, number_str, pmatch[0].rm_so, pmatch[0].rm_eo);
  printf("\n%s\n%s\n%s\nstart: %d, end: %d\n", re_template, text, number_str, pmatch[1].rm_so, pmatch[1].rm_eo);
  //regexec(preg, "jfdslfjtttsfdjlj", 1, NULL, 0);
  regfree(preg);
  perror("error");
}
