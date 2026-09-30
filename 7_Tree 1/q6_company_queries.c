/*
 * Tree 1 - Company queries: k-th boss (Challenge 66)
 * n employees form a tree, employee 1 is the general director. For every
 * query "x k" print the boss of x that is k levels higher up, or -1.
 *
 * Idea: binary lifting. up[v][b] = the 2^b-th ancestor of v (0 = none).
 * link(i, j) makes j the boss of i and fills the whole table row of i:
 *      up[i][0] = j,   up[i][b] = up[ up[i][b-1] ][b-1]
 * A query walks over the set bits of k, so it costs O(log n).
 * (A boss number that is not smaller than the employee number cannot occur
 *  in a valid tree; such a value is treated as "no boss".)
 *
 * Input : n q, the n-1 bosses of employees 2..n, then q lines "x k".
 * Output: the answer of every query.
 *
 * Sample: 5 3 / 1 3 2 2 / 4 2 / 1 2 / 1 3 -> 1 -1 -1
 */
#include <stdio.h>

#define MAXN 200005
#define LOG 18

int up[MAXN][LOG];

void link(int i,int j)
{
    int b;
    up[i][0] = j;
    for (b = 1; b < LOG; b++)
        up[i][b] = up[up[i][b - 1]][b - 1];
}

int kthBoss(int x, int k)
{
    int b;
    for (b = 0; b < LOG && x != 0; b++)
    {
        if ((k >> b) & 1)
            x = up[x][b];
    }
    return x == 0 ? -1 : x;
}

int main()
{
    int n, q, i, boss, x, k;

    scanf("%d %d", &n, &q);
    for (i = 2; i <= n; i++)
    {
        scanf("%d", &boss);
        if (boss >= i || boss < 1)
            boss = 0;
        link(i, boss);
    }

    while (q-- > 0)
    {
        scanf("%d %d", &x, &k);
        if (k >= n)
            printf("-1\n");
        else
            printf("%d\n", kthBoss(x, k));
    }
    return 0;
}
