int main(void)
{
  char a[4][3][2] = {
    {
      {'a', 'b'},
      {'c', 'd'},
      {'e', 'f'}
    },
    {
      {'g', 'h'},
      {'i', 'j'},
      {'k', 'l'}
    },
    {
      {'m', 'n'},
      {'o', 'p'},
      {'r', 'q'}
    },
    {
      {'s', 't'},
      {'v', 'u'},
      {'w', 'x'}
    }
  };

  char (*pa)[2] = &a[1][0];
  char (*ppa)[3][2] = &a[1];
  printf("(*ppa)[3][2] : %c\n", ppa[1][2][0]);
  printf("(*ppa)[3][2] : %c\n", *(*(*(ppa+1)+2)));

  printf("(*pa)[2] : %c\n", *(*(pa+5)));
  printf("(*pa)[2] : %c\n", *(*(pa+2)));

  //printf("%d\n", pa);
}
