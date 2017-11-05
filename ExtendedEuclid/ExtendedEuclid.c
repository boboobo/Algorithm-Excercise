#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>


// ** struct that store x,y,d
struct _node {
	int x;
	int y;
	int d;
};


struct _node *extended_Euclid(int a, int b)
{
	// initialize variables
	struct _node *n;
	struct _node *n1, *n2;


	if (b == 0) {
		n = (struct _node *)malloc(sizeof(struct _node));
		n->x = 1;
		n->y = 0;
		n->d = a;

		return n;	// n = (1,0,a)
	}

	n1 = extended_Euclid(b, a%b);		// recursive call

	printf("%d\n", n1->x);
	printf("%d\n", n1->y);

	// store value
	n2 = (struct _node *)malloc(sizeof(struct _node));
	n2->x = n1->y;
	n2->y = (n1->x) - (a / b)*(n1->y);
	n2->d = n1->d;

	return n2;


}

void main() {

	struct _node *n;
	int u, v;

	while (1)
	{
		printf("\n\n Type two positive integers -> ");

		scanf("%d %d", &u, &v);

		if (u < 0 || v < 0)
			continue;
		if (u == 0 || v == 0)
			break;

		n = extended_Euclid(u, v);

		printf("x is %d, y is %d, and d is %d\n", n->x, n->y, n->d);
	}


}