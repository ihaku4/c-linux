#include <stdlib.h>
#include <string.h>
#include "stringutil.h"

int is_blank(char c) {
  return c == 0xA || c == 0x20;
}

char * trim(char *s)
{
  int n;
  int i;
  for (; is_blank(*s); s++);
  n = strlen(s);
  for (i = n-1; is_blank(s[i]) && i >= 0; i--) {
    s[i] = 0x0;
  }
  return s;
}
