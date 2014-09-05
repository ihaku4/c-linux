/* binarytree.h */
#ifndef BINARYTREE_H
#define BINARYTREE_H
typedef struct node *link;
struct node {
  unsigned char item;
  link l, r;
};
link init(unsigned char VLR[], unsigned char LVR[], int n);
void pre_order(link t, void (*visit)(link));
void in_order(link t, void (*visit)(link));
void post_order(link t, void (*visit)(link));
int count(link t);
int depth(link t);
void destroy(link t);
#endif
