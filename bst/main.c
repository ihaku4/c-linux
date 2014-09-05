/* main.c */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bst.h"
#include "bst.c"
#define RANGE 100
#define N 6

void print_item(link p)
{
  printf("%d", p->item);
}

int main()
{
  int i, key;
  link root = NULL;
  srand(time(NULL));
  for (i = 0; i < N; i++)
    root = insert(root, rand() % RANGE);
  printf("\t\\tree");
  print_tree(root);
  printf("\n\n");
  while (root) {
    key = rand() % RANGE;
    if (search(root, key)) {
      printf("delete %d in tree\n", key);
      root = delete(root, key);
      printf("\t\\tree");
      print_tree(root);
      printf("\n\n");
    }
  }
}
