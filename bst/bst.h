/* bst.h */
#ifndef BST_H
#define BST_H
typedef struct node *link;
struct node {
unsigned char item;
link l, r;
};
link search(link t, unsigned char key);
link insert(link t, unsigned char key);
link delete(link t, unsigned char key);
void print_tree(link t);
#endif
