int main(void)
{
  func();
  (&func)();
  //&func();
  printf("func addr: %d\n", &func);
}

void func()
{
  printf("function is running.\n");
}
