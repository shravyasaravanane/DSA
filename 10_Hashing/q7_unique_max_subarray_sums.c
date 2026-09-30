/*
 * Hashing - Sum of unique maximum subarray sums (Challenge 97)
 * For every subarray A[l..r] take its maximum subarray sum (Kadane inside
 * it); collect the DISTINCT values obtained over all subarrays and add them.
 * Sample 1: 5 -2 7 -3 gives 5,5,10,10,-2,7,7,7,7,-3 -> 5+10-2+7-3 = 17.
 *
 * For a fixed l, extending r keeps Kadane's state (best sum ending at r and
 * best so far), so all N(N+1)/2 <= 2*10^6 values come out in O(N^2) time.
 * Values are stored in a hash set (open addressing on 64 bit keys), which
 * tells in O(1) whether a value is new; new values are added to the answer.
 * Sums reach 2*10^12 so long long is used.
 *
 * Input : N, then N integers.          Output: the sum of the unique values.
 *
 * Sample: 4 / 5 -2 7 -3 -> 17         15 / 2 3 4 5 6 7 3 4 2 7 6 8 6 4 9 -> 2021
 */
#include <stdio.h>

#define N 2005
#define BITS 22
#define SIZE (1 << BITS)

int NA[N];
long long table[SIZE];
char used[SIZE];

/* adds v to the set; returns 1 if it was not there yet */
int insert(long long v)
{
    unsigned long long h = ((unsigned long long)v * 11400714819323198485ULL) >> (64 - BITS);
    while (used[h])
    {
        if (table[h] == v)
            return 0;
        h = (h + 1) & (SIZE - 1);
    }
    used[h] = 1;
    table[h] = v;
    return 1;
}

int main()
{
    int n, l, r;
    long long cur, best, prev, sum = 0;

    scanf("%d", &n);
    for (l = 0; l < n; l++)
        scanf("%d", &NA[l]);

    for (l = 0; l < n; l++)
    {
        cur = best = NA[l];
        if (insert(best))
            sum += best;
        prev = best;
        for (r = l + 1; r < n; r++)
        {
            cur = cur > 0 ? cur + NA[r] : NA[r];
            if (cur > best)
                best = cur;
            if (best != prev)
            {
                if (insert(best))
                    sum += best;
                prev = best;
            }
        }
    }
    printf("%lld\n", sum);
    return 0;
}
