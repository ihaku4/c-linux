#include <stdio.h>
#include "stringutil.h"
#include "stringutil.c"
#define LENGHTH 1000
#define SEARCH_PATH_N 2

char *unwrap(char *s);
int is_need_remove(char c);

int main(int argc, char *argv[])
{
  FILE *fp;
  char *line;
  char *trimed_line;
  char *target_file;
  char path[LENGHTH];
  char *needle = "#include";
  char *search_path[SEARCH_PATH_N] = {"./", "/usr/include/"};
  char *ptr;
  int i;

  if (argc < 2) {
    fputs("at least 1 argument.", stderr);
    //fprintf(stderr, "at least 1 argument.");
    exit(1);
  }
  if ((fp = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "error open file %s!", argv[1]);
    exit(1);
  }
  for (line = malloc(LENGHTH*sizeof(char)); 
      fgets(line, LENGHTH, fp) != NULL; 
      line = malloc(LENGHTH*sizeof(char))) {

    // The following loop read line from file, 
    // and extends the capacity of line if the fileline is longer than 'line'.
    // ?But, how to judge if one fgets has read the whole line, but not splited.
    for (i = 0; strlen(line) == LENGHTH*(i+1)-1; i++) { 
      line = realloc(line, LENGHTH*(i+1));
      fgets(line+(LENGHTH*(i+1) - 1), LENGHTH, fp);
    }
    trimed_line = trim(line);
    ptr = strstr(trimed_line, needle);
    target_file = NULL;
    ptr && ptr == trimed_line && (target_file = ptr+(strlen(needle)));
    if (!target_file) continue;
//    fputs(target_file, stdout);
//    fputs("\n", stdout);
    target_file = trim(target_file);
//    fputs(target_file, stdout);
//    fputs("\n", stdout);
    target_file = unwrap(target_file);
    fputs(target_file, stdout);
    fputs("\n", stdout);

    fflush(stdout);

    // -------- search in paths
    // recursive search?

    free(line);
  }
}

// remove prefix and subfix like <> and "" in string.
char *unwrap(char *s)
{
  for (; is_need_remove(*s); s++);
  int len = strlen(s);
  if (is_need_remove(s[len-1])) s[len-1] = '\0';
  return s;
}

int is_need_remove(char c)
{
  char *black_rule = "<>\"";
  for (; *black_rule != '\0'; black_rule++)
    if (*black_rule == c) return 1;
  return 0;
}
