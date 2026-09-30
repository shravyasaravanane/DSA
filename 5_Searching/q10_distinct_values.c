/*
 * Searching - Distinct values in a subarray (Challenge 10)
 * The sorted array A contains the integer i exactly
 *      cnt(i) = i * floor(sqrt(i)) + ceil(i / 2)
 * times (i = 1, 2, 3 ...), so A = 1 1 2 2 2 3 3 3 3 3 ...
 * For a query "L R" (1-based) print the number of distinct values in
 * A[L..R].
 *
 * Idea: build prefix sums pre[k] = cnt(1) + ... + cnt(k). The value stored
 * at position p is the smallest k with pre[k] >= p, found by binary search
 * (pre grows like k^2.5, so k <= ~2.3 * 10^5 for positions up to 10^13).
 * As A is sorted, the distinct values in A[L..R] are all the integers
 * from value(L) to value(R):  answer = value(R) - value(L) + 1.
 * (If a query is given with L > R the two ends are swapped.)
 *
 * Input : Q, then Q lines "L R".
 * Output: the number of distinct values for every query.
 *
 * Sample: 2 / 1 3 / 1 6 -> 2 3
 */
#include <stdio.h>
#include <math.h>

#define K 300000

long long pre[K + 1];

/* smallest k such that pre[k] >= p */
int find(long long p)
{
    int l = 1, ans1 = K, mid;
    while(l<ans1)
    {
        mid = (l + ans1) / 2;
        if (pre[mid] >= p)
            ans1 = mid;
        else
            l = mid + 1;
    }
    return l;
}

int main()
{
    int q, a, b;
    long long i, s, L, R, tmp;

    pre[0] = 0;
    for (i = 1; i <= K; i++)
    {
        s = (long long)sqrt((double)i);
        while (s * s > i)
            s--;
        while ((s + 1) * (s + 1) <= i)
            s++;
        pre[i] = pre[i - 1] + i * s + (i + 1) / 2;
    }

    scanf("%d", &q);
    while (q-- > 0)
    {
        scanf("%lld %lld", &L, &R);
        if (L > R)
        {
            tmp = L;
            L = R;
            R = tmp;
        }
        a = find(L);
        b = find(R);
        printf("%d\n", b - a + 1);
    }
    return 0;
}
