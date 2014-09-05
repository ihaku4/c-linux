/* bst.c */
#include <stdlib.h>
#include <stdio.h>
#include "bst.h"
static link make_node(unsigned char item)
{
  link p = malloc(sizeof *p);
  p->item = item;
  p->l = p->r = NULL;
  return p;
}

static void free_node(link p)
{
  free(p);
}

link search(link t, unsigned char key)
{
  if (!t)
    return NULL;
  if (t->item > key)
    return search(t->l, key);
  if (t->item < key)
    return search(t->r, key);
  /* if (t->item == key) */
  return t;
}

link insert(link t, unsigned char key)
{
  if (!t)
    return make_node(key);
  if (t->item > key) /* insert to left subtree */
    t->l = insert(t->l, key);
  else /* if (t->item <= key), insert to right subtree */
    t->r = insert(t->r, key);
  return t;
}

link delete(link t, unsigned char key)
{
  link p;
  if (!t)
    return NULL;
  if (t->item > key) /* delete from left subtree */
    t->l = delete(t->l, key);
  else if (t->item < key) /* delete from right subtree */
    t->r = delete(t->r, key);
  else { /* if (t->item == key) */
    if (t->l == NULL && t->r == NULL) { /* if t is leaf node */
      free_node(t);
      t = NULL;
    }
    else if (t->l) { /* if t has left subtree */
      /* replace t with the rightmost 
         node in left subtree */
      for (p = t->l; p->r; p = p->r);
      t->item = p->item;
      t->l = delete(t->l, t->item);
    }
    else { /* if t has right subtree */
      /* replace t with the leftmost 
         node in right subtree */
      for (p = t->r; p->l; p = p->l);
      t->item = p->item;
      t->r = delete(t->r, t->item);
    }
  }
  return t;
}

void print_tree(link t)
{
  if (t) {
    printf("(");
    printf("%d", t->item);
    print_tree(t->l);
    print_tree(t->r);
    printf(")");
  }
  else printf("()");
}

