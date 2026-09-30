/*
 * Hashing - Perfume in ABC college (Challenge 94)
 * Boy x has a crush on girl b[x], girl y has a crush on boy g[y].
 * Every student beats up the crush of his/her crush:
 *      boy  x beats boy  g[b[x]]      girl y beats girl b[g[y]]
 * (only if that is somebody else).
 *  1. the maximum number of beatings received by one student;
 *  2. the number of pairs of students who beat each other up.
 * Every student beats exactly one student, so arrays are enough: count the
 * beatings received (recv arrays) and detect mutual pairs with
 * target[target[x]] == x (counted once with x < target[x]).
 *
 * Input : T, per test case: N, the crushes of the boys, the crushes of the
 *         girls.        Output: "max pairs" per test case.
 *
 * Sample: 2 / 3 / 2 2 1 / 3 2 1 / 4 / 2 3 4 1 / 2 3 4 1  ->  1 0 / 1 4
 */
#include <stdio.h>
#include <stdbool.h>

#define MAXN 100010

int b[MAXN], g[MAXN], tb[MAXN], tg[MAXN], recvB[MAXN], recvG[MAXN];

int main()
{
    int t, tc = 0, n, i, max, pairs;

    scanf("%d", &t);
    while(true)
    {
        if (tc == t)
            break;
        tc++;

        scanf("%d", &n);
        for (i = 0; i < MAXN; i++)
            b[i] = g[i] = tb[i] = tg[i] = recvB[i] = recvG[i] = 0;
        for (i = 1; i <= n; i++)
            scanf("%d", &b[i]);
        for (i = 1; i <= n; i++)
            scanf("%d", &g[i]);

        /* whom does everybody beat up? (0 = nobody / invalid input) */
        for (i = 1; i <= n; i++)
        {
            if (b[i] >= 1 && b[i] <= n)
                tb[i] = g[b[i]];
            if (g[i] >= 1 && g[i] <= n)
                tg[i] = b[g[i]];
            if (tb[i] == i || tb[i] > n)
                tb[i] = 0;
            if (tg[i] == i || tg[i] > n)
                tg[i] = 0;
            if (tb[i])
                recvB[tb[i]]++;
            if (tg[i])
                recvG[tg[i]]++;
        }

        max = 0;
        pairs = 0;
        for (i = 1; i <= n; i++)
        {
            if (recvB[i] > max)
                max = recvB[i];
            if (recvG[i] > max)
                max = recvG[i];
            if (tb[i] && i < tb[i] && tb[tb[i]] == i)
                pairs++;
            if (tg[i] && i < tg[i] && tg[tg[i]] == i)
                pairs++;
        }
        printf("%d %d\n", max, pairs);
    }
    return 0;
}
