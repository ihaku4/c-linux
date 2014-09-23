#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringutil.h"
#define LENGHTH 1000
#define SEARCH_PATH_N 2

char *unwrap(char *s);
int is_need_remove(char c);
int traverse_include_files(const char *filename);
void read_file(FILE *file);
void process_line(char *line);
char *get_file_name(char* line);

int main(int argc, char *argv[])
{
  int result;

  if (argc < 2) {
    fputs("at least 1 argument.", stderr);
    exit(1);
  }
  result = traverse_include_files(argv[1]);
  return result;
}

int traverse_include_files(const char *filename)
{
  FILE *fp;
  if ((fp = fopen(filename, "r")) == NULL) {
    return 1;
  }
  read_file(fp);
  fclose(fp);
  return 0;
  
}

void read_file(FILE *file)
{
  char *line;
  int i;

  for (line = malloc(LENGHTH*sizeof(char)); 
      fgets(line, LENGHTH, file) != NULL; 
      line = malloc(LENGHTH*sizeof(char))) {

    // The following loop read line from file, 
    // and extends the capacity of line if the fileline is longer than 'line'.
    // ?But, how to judge if one fgets has read the whole line, but not splited.
    for (i = 0; strlen(line) == LENGHTH*(i+1)-1; i++) { 
      line = realloc(line, LENGHTH*(i+1));
      fgets(line+(LENGHTH*(i+1) - 1), LENGHTH, file);
    }
    process_line(line);
    free(line);
  }
}

void process_line(char *line)
{
  char *target_file = NULL;
  char path[LENGHTH];
  char *search_path[SEARCH_PATH_N] = {"./", "/usr/include/"};
  int i, len;

  if ((target_file = get_file_name(line)) == NULL) return;
  for (i = 0, len = SEARCH_PATH_N; i < len; i++) {
    int path_len = strlen(search_path[i]);
    int filename_len = strlen(target_file);
    memcpy(path, search_path[i], path_len);
    memcpy(path + path_len, target_file, filename_len);
    *(path + path_len + filename_len) = '\0';
    if (traverse_include_files(path) == 0) {
      printf("%s\n", path);
      break;
    }
    if (i == len-1) {
      printf("%s --- cannot find ---\n", path);
    } 
  }
}

char *get_file_name(char* line)
{
  char *needle = "#include";
  char *ptr;
  char *trimed_line;
  char *target_file = NULL;

  trimed_line = trim(line);
  ptr = strstr(trimed_line, needle);
  ptr && ptr == trimed_line && (target_file = ptr+(strlen(needle)));
  if (!target_file) return NULL;
  target_file = trim(target_file);
  target_file = unwrap(target_file);
  return target_file;
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
