/*
 * Tree 2 - Ghost of the day / Consistency Trophy (Challenge 78)
 * Every day one ghost (given by its age) wins the "Ghost of the Day" title.
 * After the title is given, the Consistency Trophy goes to the ghost with the
 * most titles so far (the eldest one if several ghosts are tied).
 * For every day print the age of the trophy winner and his number of titles.
 *
 * Idea: only the ghost that won today gets one more title, so the current
 * trophy winner changes only if this ghost now has more titles than the
 * winner, or the same number and he is older. It is enough to remember
 * (best age, best count) and update it in O(1) per day.
 * The ages go up to 10^9, so they are sorted and compressed first; the
 * distinct ages are collected by looking at neighbouring elements of the
 * sorted array and every day's age is found with a binary search.
 *
 * Input : N M, then the N ages of the daily winners.
 * Output: N lines "age titles".
 *
 * Sample: 7 5 / 1 3 1 3 2 2 2 -> 1 1 / 3 1 / 1 2 / 3 2 / 3 2 / 3 2 / 2 3
 */
#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}

int main()
{
    int n, m, i, d, lo, hi, mid, bestAge = 0, bestCnt = 0;
    int *day, *sorted, *uniq, *cnt;

    scanf("%d %d", &n, &m);
    day    = (int *)malloc((n + 1) * sizeof(int));
    sorted = (int *)malloc((n + 1) * sizeof(int));
    uniq   = (int *)malloc((n + 1) * sizeof(int));
    cnt    = (int *)calloc(n + 1, sizeof(int));

    for (i = 0; i < n; i++)
    {
        scanf("%d", &day[i]);
        sorted[i] = day[i];
    }
    qsort(sorted, n, sizeof(int), compare);

    /* distinct ages */
    d = 0;
    uniq[d++] = sorted[0];
    for(i = 0;i<n-1;i++)
        if (sorted[i] != sorted[i + 1])
            uniq[d++] = sorted[i + 1];

    for (i = 0; i < n; i++)
    {
        lo = 0;
        hi = d - 1;
        while (lo < hi)
        {
            mid = (lo + hi) / 2;
            if (uniq[mid] < day[i])
                lo = mid + 1;
            else
                hi = mid;
        }
        cnt[lo]++;
        if (cnt[lo] > bestCnt || (cnt[lo] == bestCnt && day[i] > bestAge))
        {
            bestCnt = cnt[lo];
            bestAge = day[i];
        }
        printf("%d %d\n", bestAge, bestCnt);
    }
    return 0;
}
