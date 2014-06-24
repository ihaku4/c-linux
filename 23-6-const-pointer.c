int main(void)
{

  int a[10];
  const char **p_2_p_2_const_char = a;
  char *const *p_2_const_p_2_char = a;
  char **const const_p_2_p_2_char = a;

  char const * const * const const_p_2_const_p_2_const_char = a;

  (**p_2_p_2_const_char)++;
  (*p_2_p_2_const_char)++;
  (p_2_p_2_const_char)++;

  (**p_2_const_p_2_char)++;
  (*p_2_const_p_2_char)++;
  (p_2_const_p_2_char)++;

  (**const_p_2_p_2_char)++;
  (*const_p_2_p_2_char)++;
  (const_p_2_p_2_char)++;

  (**const_p_2_const_p_2_const_char)++;
  (*const_p_2_const_p_2_const_char)++;
  (const_p_2_const_p_2_const_char)++;
}
