/*
 * Tree 2 - Maximum pounds from the ticket sales (Challenge 80)
 * M rows with X[i] empty seats. A ticket costs as many pounds as the number
 * of empty seats of its row at that moment. N fans buy one ticket each, one
 * by one. Find the maximum money the club can collect.
 *
 * Idea (greedy + max-heap): every fan should get the ticket of the row with
 * the most empty seats (that is the most expensive one). Keep the seat
 * counts in a max-heap: add arr[0] to the total, decrease arr[0] by one and
 * restore the heap with heapify(arr, M, 0). Building the heap costs O(M),
 * every sale O(log M).
 *
 * Input : M N, then the M seat counts.
 * Output: the maximum amount in pounds.
 *
 * Sample: 3 4 / 1 2 4 -> 11 ; 8 4 / 3 7 1 2 4 7 5 9 -> 31
 */
#include <stdio.h>
#include <stdlib.h>

/* sift the element at index i down in the max-heap arr[0..n-1] */
void heapify(int arr[],int n,int i)
{
    int largest = i, l = 2 * i + 1, r = 2 * i + 2, t;
    while (1)
    {
        largest = i;
        if (l < n && arr[l] > arr[largest])
            largest = l;
        if (r < n && arr[r] > arr[largest])
            largest = r;
        if (largest == i)
            break;
        t = arr[i];
        arr[i] = arr[largest];
        arr[largest] = t;
        i = largest;
        l = 2 * i + 1;
        r = 2 * i + 2;
    }
}

int main()
{
    int m, n, i;
    int *arr;
    long long total = 0;

    scanf("%d %d", &m, &n);
    arr = (int *)malloc(m * sizeof(int));
    for (i = 0; i < m; i++)
        scanf("%d", &arr[i]);

    for (i = m / 2 - 1; i >= 0; i--)
        heapify(arr, m, i);

    for (i = 0; i < n; i++)
    {
        if (arr[0] <= 0)
            break;
        total += arr[0];
        arr[0]--;
        heapify(arr, m, 0);
    }
    printf("%lld\n", total);
    return 0;
}
