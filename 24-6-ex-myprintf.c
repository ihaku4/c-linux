#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void iprint(int n) {
  if (n > 9) {
    int a = n / 10;
    n -= 10 * a;
    iprint(a);
  }
  putchar('0'+n);
}

void myprintf(const char *format, ...)
{
  va_list ap;
  char c;
  va_start(ap, format);
  while (c = *format++) {
    if (c != '%') {
      putchar(c);
      continue;
    }
    c = *format++;
    if (!c) break;
    switch (c) {
      case 'c': {
        /* char is promoted to int when passed through '...' */
        char ch = va_arg(ap, int);
        putchar(ch);
        break;
      }
      case 's': {
        char *p = va_arg(ap, char *);
        fputs(p, stdout);
        break;
      }
      case 'd': {
        int i = va_arg(ap, int); 
        //char *p = itoa(i);
        //fputs(p, stdout);
        //putchar(i);
        iprint(i);
        break;
      }
      default:
        putchar(c);
    }
  }
  va_end(ap);
  printf("\n--------------- end of myprintf -----------------\n");
}

int main(void)
{
  myprintf("c\ts\n", '1', "hello");
  myprintf("%c\t%s\n", '1', "hello");
  myprintf("%c\t%s\t%d\n", '1', "hello", 987);
  return 0;
}
