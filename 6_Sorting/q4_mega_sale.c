/*
 * Sorting - Mega Sale (Challenge 14)
 * n laptops with prices ai. Some prices are negative (the owner pays
 * APPU to take the laptop). APPU can carry at most m laptops.
 * Print the maximum money he can earn.
 * Sort the prices ascending (bubble sort) and add the negative prices
 * among the first m laptops.
 *
 * Input : T, then for every test case: n m, and the n prices.
 *
 * Sample: 5 3 / -6 0 35 -2 4       -> 8
 *         6 2 / -4 5 0 -1 2 1      -> 5
 *         7 4 / 6 1 0 -2 2 -4 3    -> 6
 */
#include <stdio.h>

void bubble_sort(int arr[],int no)
{
    int i, j, temp, swapped;
    for (i = 0; i < no - 1; i++)
    {
        swapped = 0;
        for (j = 0; j < no - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped)
            break;
    }
}

int MEGA_SALE(int arr[],int no,int k)
{
    int i, profit = 0;
    bubble_sort(arr, no);
    for (i = 0; i < k && i < no; i++)
    {
        if (arr[i] < 0)
            profit += -arr[i];
        else
            break;
    }
    return profit;
}

int main()
{
    int t, n, m, i;
    int arr[100];

    scanf("%d", &t);
    while (t-- > 0)
    {
        scanf("%d %d", &n, &m);
        for (i = 0; i < n; i++)
            scanf("%d", &arr[i]);
        printf("%d\n", MEGA_SALE(arr, n, m));
    }
    return 0;
}
