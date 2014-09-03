#include <stdio.h>
#include "binarytree.h"
#include "binarytree.c"

char path[100];

void print_item(link p)
{
//	printf("%d", p->item);
	printf("%c", p->item);
}

int main()
{
//	unsigned char pre_seq[] = { 4, 2, 1, 3, 6, 5, 7 };
//	unsigned char in_seq[] = { 1, 2, 3, 4, 5, 6, 7 };
	unsigned char in_seq[] = { 'T', 'b', 'H', 'V', 'h', '3', 'o', 'g', 'P', 'W', 'F', 'L', 'u', 'A', 'f', 'G', 'r', 'm', '1', 'x', 'J', '7', 'w', 'e', '0', 'i', 'Q', 'Y', 'n', 'Z', '8', 'K', 'v', 'q', 'k', '9', 'y', '5', 'C', 'N', 'B', 'D', '2', '4', 'U', 'l', 'c', 'p', 'I', 'E', 'M', 'a', 'j', '6', 'S', 'R', 'O', 'X', 's', 'd', 'z', 't' };
	unsigned char post_seq[] = { 'T', 'V', 'H', 'o', '3', 'h', 'P', 'g', 'b', 'F', 'f', 'A', 'u', 'm', 'r', '7', 'J', 'x', 'e', 'w', '1', 'Y', 'Q', 'i', '0', 'Z', 'n', 'G', 'L', 'K', 'y', '9', 'k', 'q', 'v', 'N', 'D', 'B', 'C', '5', '4', 'c', 'l', 'U', '2', '8', 'E', 'I', 'R', 'S', '6', 'j', 'd', 's', 'X', 'O', 'a', 'M', 'p', 'W', 't', 'z' };
	//link root = init(pre_seq, in_seq, 7);
	//link root = init(pre_seq, in_seq, 62);
	link root = init_by_post_and_in(post_seq, in_seq, 62);
	pre_order(root, print_item);
	putchar('\n');
	in_order(root, print_item);
	putchar('\n');
	post_order(root, print_item);
	putchar('\n');
	printf("count=%d depth=%d\n", count(root), 
	depth(root));
	memset(path, '\0', 100);
	deepest_path(root, path, depth(root), 1);
	printf("deepest path: %s", path);
	printf("deepest path: xxxx");

	destroy(root);
	return 0;
}
