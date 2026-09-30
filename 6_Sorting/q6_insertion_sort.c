/*
 * Sorting - Insertion Sort (Challenge 16)
 * Input : N, then N numbers.
 * Output: line 1 -> the state of the array after the 3rd iteration
 *         line 2 -> the final sorted array
 *
 * Sample: 5 / 64 25 22 90 35
 *   -> 22 25 64 90 35
 *      22 25 35 64 90
 *         5 / 16 21 22 10 35
 *   -> 16 21 22 10 35
 *      10 16 21 22 35
 */
#include <stdio.h>
#include <stdlib.h>

void printArray(int arr[],int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d", arr[i]);
        if (i < n - 1)
            printf(" ");
    }
    printf("\n");
}

void insertionSort(int arr[],int n)
{
    int i, j, key;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;

        /* iterations are counted from index 0 (i = 0, 1, 2), so the 3rd
           iteration is i = 2: the first three elements are now sorted */
        if (i == 2)
            printArray(arr, n);
    }
}

int main()
{
    int n, i;
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    insertionSort(arr, n);
    printArray(arr, n);

    free(arr);
    return 0;
}
