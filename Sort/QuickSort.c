#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#define MAX 50

int A[MAX];

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
    pivot = A[p];
    h = p;

    for(k=p+1; k<=r; k++)
    {
        if(A[k] < pivot)
        {
            h = h+1;
            swap(&A[h], &A[k]);
        }
    }
    swap(&A[p], &A[h]);

    return h;
}

void quick_sort(int p, int r)
{
    int q;

    if(p < r)
    {
        q = partition(p,r);
        quick_sort(p, q-1);
        quick_sort(q+1, r);
    }
}

void main()
{
    int i;
    FILE *fp;
    fp = fopen("input.dat", "r");

    for(i=0; i<MAX; i++)
        fscanf(fp, "%d", &A[i]);

    for(i=0; i<MAX; i++)
        printf("%d ", A[i]);
    printf("\n");

    quick_sort(0, MAX-1);

    for(i=0; i<MAX; i++)
        printf("%d ", A[i]);
    printf("\n");
}
