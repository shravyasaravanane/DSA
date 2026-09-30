/*
 * Sorting - Selection Sort (Challenge 12)
 * Input : N, then N numbers.
 * Output: the numbers sorted in ascending order using selection sort.
 *
 * Sample: 5 / 15 17 11 25 1        -> 1 11 15 17 25
 *         6 / 65 45 27 21 25 11    -> 11 21 25 27 45 65
 */
#include <stdio.h>
#include <stdlib.h>

void swap(int *xp,int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void selectionSort(int arr[],int n)
{
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        if (min_idx != i)
            swap(&arr[min_idx], &arr[i]);
    }
}

void printArray(int arr[],int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf("%d", arr[i]);
        if (i < size - 1)
            printf(" ");
    }
    printf("\n");
}

int main()
{
    int n, i;
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    selectionSort(arr, n);
    printArray(arr, n);

    free(arr);
    return 0;
}
