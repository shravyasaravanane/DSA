/*
 * Searching - Third largest element (Challenge 6)
 * Find the third largest (distinct) number of the array in a single pass by
 * tracking the three biggest values: first > second > third.
 *
 * Input : N, then N integers.
 * Output: The third Largest element is X
 *         (or "Invalid Input" when there is no third largest value)
 *
 * Sample: 6 / 1 14 2 16 10 20        -> The third Largest element is 14
 *         7 / 19 -10 20 14 2 16 10   -> The third Largest element is 16
 */
#include <stdio.h>
#include <limits.h>

void thirdLargest(int arr[],int arr_size)
{
    int first = INT_MIN, second = INT_MIN, third = INT_MIN;
    int i, found = 0;

    for (i = 0; i < arr_size; i++)
    {
        int v = arr[i];
        if (found >= 1 && v == first)
            continue;
        if (found >= 2 && v == second)
            continue;
        if (found >= 3 && v == third)
            continue;

        if (found == 0 || v > first)
        {
            third = second;
            second = first;
            first = v;
            found++;
        }
        else if (found == 1 || v > second)
        {
            third = second;
            second = v;
            found++;
        }
        else if (found == 2 || v > third)
        {
            third = v;
            found++;
        }
    }

    if (found < 3)
        printf("Invalid Input\n");
    else
        printf("The third Largest element is %d\n", third);
}

int main()
{
    int n, i;
    int arr[1000];

    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    thirdLargest(arr, n);
    return 0;
}
