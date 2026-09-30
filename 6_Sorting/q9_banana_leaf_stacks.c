/*
 * Sorting - Banana leaf stacks (Challenge 19)
 * There are N stacks with K leaves each (values given from top to
 * bottom). Irfan takes exactly P leaves. To take a leaf he must take all
 * the leaves above it in that stack, so from every stack he takes a
 * prefix of leaves. Maximise the total attractive value.
 *
 * Dynamic programming: dp[j] = best total using exactly j leaves from the
 * stacks processed so far. For each stack try taking t = 0..K leaves
 * (value = prefix sum of the first t leaves).
 *
 * Input : T, then for every test case: N K P and N lines of K integers.
 * Output: the maximum total value for every test case.
 *
 * Sample: 2 4 5 / 10 10 100 30 / 80 50 10 50      -> 250
 *         3 2 3 / 80 80 / 20 20 / 15 50           -> 180
 */
#include <stdio.h>

int max(int a,int b)
{
    return a > b ? a : b;
}

int main()
{
    int t, n, k, p, j, x;
    int prefix[31];
    int dp[1505], next[1505];

    scanf("%d", &t);
    while (t-- > 0)
    {
        scanf("%d %d %d", &n, &k, &p);

        /* dp[0] = 0, and -1 marks "not reachable" */
        for (j = 0; j <= p; j++)
            dp[j] = -1;
        dp[0] = 0;

        for(int i = 0;i < n;i++)
        {
            /* prefix[x] = sum of the top x leaves of this stack */
            prefix[0] = 0;
            for (x = 1; x <= k; x++)
            {
                int leaf;
                scanf("%d", &leaf);
                prefix[x] = prefix[x - 1] + leaf;
            }

            for (j = 0; j <= p; j++)
                next[j] = -1;

            for (j = 0; j <= p; j++)
            {
                for (x = 0; x <= k && x <= j; x++)
                {
                    if (dp[j - x] != -1)
                        next[j] = max(next[j], dp[j - x] + prefix[x]);
                }
            }

            for (j = 0; j <= p; j++)
                dp[j] = next[j];
        }

        printf("%d\n", dp[p]);
    }
    return 0;
}
