#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 50

int ex1[MAX];
int ex2[MAX];

int quick_sort_counter;
int insertion_sort_counter;

void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int partition(int p, int r)
{
	int pivot, h, k;
	pivot = ex1[p];
	h = p;

	quick_sort_counter = 0;

	for (k = p + 1; k <= r; k++)
	{
		if (ex1[k] < pivot)
		{
			h = h + 1;
			swap(&ex1[h], &ex1[k]);
		}
		quick_sort_counter++;
	}
	swap(&ex1[p], &ex1[h]);

	return h;
}

void quick_sort(int p, int r)
{
	int q;

	if (p < r)
	{
		q = partition(p, r);
		quick_sort(p, q - 1);
		quick_sort(q + 1, r);
	}
}

void insertion_sort(int A[], int n)
{
    insertion_sort_counter = 0;
    int i,j,tmp;
    for(i=1; i<n; i++)
    {
        tmp = A[i];

        for(j=i; A[j-1] > tmp && j >0; j--)
        {
            A[j] = A[j-1];
            insertion_sort_counter++;
        }

        A[j] = tmp;
    }
}

void main()
{
    int i;
    FILE *data1, *data2;
    data1 = fopen("input.dat", "r");
	data2 = fopen("input.dat", "r");

    for(i = 0; i<MAX; i++)
    {
        fscanf(data1, "%d", &ex1[i]);
		fscanf(data2, "%d", &ex2[i]);
    }

	
	puts("--------- Quick Sort ---------");
	quick_sort(0, MAX-1);
	for (i = 0; i<MAX; i++)
	{
		printf("%d  ", ex1[i]);
	}
	printf("\n Quick sort runs %d comparisons. \n", quick_sort_counter);



    puts("--------- Insertion Sort ---------");
    insertion_sort(ex2, MAX);
    for(i = 0; i<MAX; i++)
    {
        printf("%d  ", ex2[i]);
    }
    printf("\n Insertion sort runs %d comparisons. \n", insertion_sort_counter);

	int a;
	scanf("%d", &a);

}
