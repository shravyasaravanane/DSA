/*
 * Searching - Train journey (Challenge 9)
 * N train routes must be taken in order; route i runs only on days that
 * are multiples of Xi, and several trains can be taken on the same day.
 * Find the latest day on which the first train can be taken so that the
 * whole journey still finishes by day D.
 *
 * Idea (greedy from the back): the last train should leave as late as
 * possible -> the biggest multiple of X[N] that is <= D. That day becomes
 * the new limit for the previous route, and so on up to the first train.
 *      D = (D / X[i]) * X[i]   for i = N .. 1
 *
 * Input : T, then for every case: N D and the N values Xi.
 * Output: the latest starting day for every case.
 *
 * Sample: 3 100 / 31 71 21 -> 62 ; 4 100 / 11 16 51 50 -> 44 ; 1 1 / 1 -> 1
 */
#include <stdio.h>

int main()
{
    int T, n;
    long long D;
    long long x[1005];

    scanf("%d", &T);
    for(int t=0;t<T;t++)
    {
        scanf("%d %lld", &n, &D);
        for (int i = 0; i < n; i++)
            scanf("%lld", &x[i]);

        for(int i=n-1;i>=0;i--)
            D = (D / x[i]) * x[i];

        printf("%lld\n", D);
    }
    return 0;
}
