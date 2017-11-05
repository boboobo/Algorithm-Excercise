#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

int A[MAX];

void insertion_sort(int A[], int n)
{
    int i,j,tmp;
    for(i=1; i<n; i++)
    {
        tmp = A[i];

        for(j=i; A[j-1] > tmp && j >0; j--)
        {
            A[j] = A[j-1];
        }

        A[j] = tmp;
    }
}

void main()
{
    int i;
    FILE *data;
    data = fopen("input.dat", "r");

    for(i = 0; i<MAX; i++)
    {
        fscanf(data, "%d", &A[i]);
    }


    puts("--------- insertion sort ---------");

    insertion_sort(A, MAX);


    for(i = 0; i<MAX; i++)
    {
        printf("%d  ", A[i]);
    }

}
