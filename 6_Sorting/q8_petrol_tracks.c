/*
 * Sorting - Petrol for the sub-tracks (Challenge 18)
 * The track has N sub-tracks. K is the maximum number of kilometres the
 * vehicle can go on each sub-track. Every unit of petrol added increases
 * the distance the vehicle can cover by one.
 * The longest sub-track decides how much extra petrol is needed:
 *   longest > K  -> extra petrol = longest - K
 *   otherwise    -> no extra petrol is needed, print -1
 * The sub-tracks are sorted and the last (largest) one is used.
 *
 * Input : T, then for every test case: N K, and the N distances.
 * Output: the minimum units of petrol for every test case.
 *
 * Sample: 5 6 / 2 5 4 5 2         -> -1
 *         5 3 / 1 6 3 5 2         -> 3
 *         5 6 / 12 15 14 15 12    -> 9
 *         5 3 / 11 61 31 51 21    -> 58
 */
#include <stdio.h>

void sort(int a[],int n)
{
    int i, j, temp;
    for(i=0;i<n-1;i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int t, n, k, i;
    int a[100000];

    scanf("%d", &t);
    while (t-- > 0)
    {
        scanf("%d %d", &n, &k);
        for (i = 0; i < n; i++)
            scanf("%d", &a[i]);

        sort(a, n);

        if (a[n - 1] > k)
            printf("%d\n", a[n - 1] - k);
        else
            printf("-1\n");
    }
    return 0;
}
