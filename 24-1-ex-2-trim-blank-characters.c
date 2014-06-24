int is_blank(char c);
char *shrink_space(char *dest, const char *src, int n);

char *shrink_space(char *dest, const char *src, int n)
{
  int i, j;
  for (i = 0, j = 0; i < n && src[i] != '\0'; i++) {
    if (!is_blank(src[i]))
      dest[j++] = src[i];
    else if ((j > 0 && dest[j-1] != ' '))
      dest[j++] = ' ';
  }
  dest[j] = '\0';
  return dest;
}

int is_blank(char c) {
  char blank_characters[4] = {' ', '\t', '\n', '\r'};
  int i;
  for (i = 0; i < 4; i++)
    if (blank_characters[i] == c) return 1;
  return 0;
}

int main(void)
{
  char t[1000] = "This Content hoho        is ok\
  		ok?\
      \
      	  file system \
uttered words   	ok ok		      ?\
end.";
  char t_cp[1000];
  shrink_space(t_cp, t, 1000);
  printf("%s\n%s\n", t_cp, t);
}
