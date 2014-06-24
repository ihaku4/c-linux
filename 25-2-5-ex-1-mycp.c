#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  char *src_file_name = argv[1], *dst_file_name = argv[2];
  FILE *fp_src, *fp_dst;
  int ch;

  printf("src : %s, dst : %s\n", src_file_name, dst_file_name);
  if ( (fp_src = fopen(src_file_name, "r")) == NULL) {
    perror("Open file src_file\n");
    exit(1);
  }
  if ( (fp_dst = fopen(dst_file_name, "w")) == NULL) {
    perror("Open file dst_file\n");
    exit(1);
  }
  printf("start copying\n");
  while ( (ch = fgetc(fp_src)) != EOF)
    fputc(ch, fp_dst);
  fclose(fp_src);
  fclose(fp_dst);
  return 0;
}
