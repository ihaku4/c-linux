char *my_strcpy(const char *src, char *dest)
{
  int i;
  for (i = 0; src[i] != '\0'; dest[i] = src[i], i++) ;
  dest[i] = '\0';
  return dest;
}

int main(void)
{
//  char *str = "qwetyt";
//  char *cp_str;
  char str[10] = "qwetyt";
  char cp_str[10];
  my_strcpy(str, cp_str);
  printf("%s\n", cp_str);
  my_strcpy("plaintext", cp_str);
  printf("%s\n", cp_str);
}
