#include <signal.h>

//long long a;
sig_atomic_t a;
int main(void)
{
  a = 5;
  return 0;
}
