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

link init_by_post_and_in(unsigned char LRV[], unsigned char LVR[], int n)
{
	link t;
	int k;
	if (n <= 0)
		return NULL;
	for (k = 0; LRV[n-1] != LVR[k]; k++);
	t = make_node(LRV[n-1]);
	t->l = init_by_post_and_in(LRV, LVR, k);
	t->r = init_by_post_and_in(LRV+k, LVR+1+k, n-k-1);
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

int deepest_path(link t, char *path, int depth, int current_depth)
{
	int result;
	printf("visit: %c. level: %d\n", t->item, current_depth);
	path[current_depth-1] = t->item;
	if (depth == current_depth) return 1;
	if (t->l) {
		result = deepest_path(t->l, path, depth, current_depth+1);
		if (result) return result;
	}
	if (t->r) {
		return deepest_path(t->r, path, depth, current_depth+1);
	}
	return 0;
}
