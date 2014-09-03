/* binarytree.c */
#include <stdlib.h>
#include "binarytree.h"

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

link init(unsigned char VLR[], unsigned char LVR[], int n)
{
  link t;
  int k;
  if (n <= 0)
    return NULL;
  for (k = 0; VLR[0] != LVR[k]; k++);
  t = make_node(VLR[0]);
  t->l = init(VLR+1, LVR, k);
  t->r = init(VLR+1+k, LVR+1+k, n-k-1);
  return t;
}

void pre_order(link t, void (*visit)(link))
{
  if (!t)
    return;
  visit(t);
  pre_order(t->l, visit);
  pre_order(t->r, visit);
}

void in_order(link t, void (*visit)(link))
{
  if (!t)
    return;
  in_order(t->l, visit);
  visit(t);
  in_order(t->r, visit);
}

void post_order(link t, void (*visit)(link))
{
  if (!t)
    return;
  post_order(t->l, visit);
  post_order(t->r, visit);
  visit(t);
}

int count(link t)
{
  if (!t)
    return 0;
  return 1 + count(t->l) + count(t->r);
}

int depth(link t)
{
  int dl, dr;
  if (!t)
    return 0;
  dl = depth(t->l);
  dr = depth(t->r);
  return 1 + (dl > dr ? dl : dr);
}

void destroy(link t)
{
  post_order(t, free_node);
}

