#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>
#define NMATCH 2
#define MAXSIZE 1000

int main(void)
{
  // ? fail to locate substring when use 'regex_t *' rather than 'regex_t'
  //regex_t *preg;
  regex_t preg;
  regmatch_t pmatch[NMATCH];
  const char *number_str = "0123456789";
  //const char *text = "jfdslfjtttsfiiid tttdsdiiiilj";
  //const char *re_template = "t\\(t\\)t.*\1";
  const char *text = "jfdslfj ttt ttt dsdiiiilj";
  const char *re_template = "\\(ttt\\) \\1";
//  char       *text = "a very simple simple simple string";
//  char       *re_template = "\\(sim[a-z]le\\) \\1";
  int res;
  char errbuf[MAXSIZE];
  //preg = malloc(sizeof(preg));
  //if (regcomp(preg, "ttt", REG_EXTENDED|REG_ICASE) == 0) {
  //if (regcomp(preg, re_template, REG_EXTENDED|REG_ICASE|REG_NOSUB) != 0) {
  //if ((res = regcomp(preg, re_template, REG_EXTENDED|REG_ICASE) != 0)) {
  if ((res = regcomp(&preg, re_template, 0) != 0)) {
    fputs("regcomp fail\n", stderr);
    regerror(res, &preg, errbuf, MAXSIZE);
    fputs("regerror out: ", stderr);
    fputs(errbuf, stderr);
    exit(1);
  }
  //if ((res = regexec(preg, text, NMATCH, pmatch, REG_NOTBOL|REG_NOTEOL) != 0)) {
  if ((res = regexec(&preg, text, NMATCH, pmatch, 0) != 0)) {
    fputs("regexec fail\n", stderr);
    regerror(res, &preg, errbuf, MAXSIZE);
    fputs("regerror out: ", stderr);
    fputs(errbuf, stderr);
    exit(1);
  }
  //regexec(preg, text, NMATCH, pmatch, REG_NOTBOL);
  printf("\n%s\n%s\n%s\nstart: %d, end: %d\n", re_template, text, number_str, pmatch[0].rm_so, pmatch[0].rm_eo);
  printf("\n%s\n%s\n%s\nstart: %d, end: %d\n", re_template, text, number_str, pmatch[1].rm_so, pmatch[1].rm_eo);
  //regexec(preg, "jfdslfjtttsfdjlj", 1, NULL, 0);
  regfree(&preg);
  perror("error");
  return 0;
}
