#include <stdio.h>
#include "stringutil.h"
#include "stringutil.c"
#define LENGHTH 1000

int main(int argc, char *argv[])
{
  FILE *fp;
  char *line;
  char *needle = "#include";
  char *ptr;
  int i;

  if (argc < 2) {
    fputs("at least 1 argument.", stderr);
    //fprintf(stderr, "at least 1 argument.");
    exit(1);
  }
  if (fp = fopen(argv[1], "r") == NULL) {
    fprintf(stderr, "error open file %s!", argv[1]);
    exit(1);
  }
  for (line = malloc(LENGHTH*sizeof(char)); fgets(line, LENGHTH, fp) != NULL; line = malloc(LENGHTH*sizeof(char))) {
    //for (i = 0; fgets(line+(LENGHTH*i - 1), LENGHTH, fp) != NULL; i++) {
    for (i = 0; strlen(line) == LENGHTH*(i+1)-1; i++) { // ? how to jundge if one fgets has read the whole line, but not splited.
      line = realloc(line, LENGHTH*(i+1));
      fgets(line+(LENGHTH*(i+1) - 1), LENGHTH, fp);
    }
    line = trim(line);
    ptr = strstr(line, needle);
    ptr && fputs(ptr, stdout);

    free(line);
  }
}
