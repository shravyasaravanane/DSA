/*
 * Graph - Teddy and the tokens of Wonderland (Challenge 81)
 * n cities, m roads, k token types with cost c[i]. Every road needs a set
 * of tokens (only shown, so one token can serve any number of roads).
 * Choose tokens of minimum total cost so that all cities are connected.
 *
 * Key fact: c[i] >= 2*c[i-1]  =>  c[i] > c[1] + c[2] + ... + c[i-1].
 * So a more expensive token is never worth buying if the cities can be
 * connected without it. Greedy from the most expensive token down:
 *   for token i = k .. 1:
 *       allowed = tokens already bought + all tokens cheaper than i
 *       if the graph is connected using only roads whose tokens are inside
 *       "allowed"  -> token i is NOT needed
 *       otherwise  -> buy token i
 * Since c[i] >= 2^(i-1) and c[i] <= 10^18, k is at most 60, so every token
 * fits in one bit of an unsigned 64 bit mask and the check is a DSU pass.
 *
 * Input : n m k / c1..ck / m lines "u v l t1..tl".
 * Output: the minimum cost, or -1 if the graph cannot be connected at all.
 *
 * Sample: 3 3 4 / 1 2 5 10 / 1 2 2 1 2 / 1 3 1 3 / 2 3 1 4  -> 8
 */
#include <stdio.h>

#define MAXN 100005

typedef unsigned long long ull;

int par[MAXN];
int eu[MAXN], ev[MAXN];
ull emask[MAXN];     /* bit t is set when the road needs token t */

int find(int x)
{
    while (par[x] != x)
    {
        par[x] = par[par[x]];
        x = par[x];
    }
    return x;
}

/* 1 if all cities get connected using roads whose tokens are all allowed */
int connected(int n,int m,ull allowed)
{
    int i, a, b, parts = n;
    for(i=1;i<=n;++i)
        par[i] = i;
    for (i = 0; i < m; i++)
    {
        if ((emask[i] & ~allowed) == 0)
        {
            a = find(eu[i]);
            b = find(ev[i]);
            if (a != b)
            {
                par[a] = b;
                parts--;
            }
        }
    }
    return parts == 1;
}

int main()
{
    int n, m, k, i, j, l, t, u, v, cnt = 0;
    ull c[70], mask, allowed, chosen = 0, cost = 0;

    scanf("%d %d %d", &n, &m, &k);
    for (i = 1; i <= k; i++)
        scanf("%llu", &c[i]);

    for (j = 0; j < m; j++)
    {
        scanf("%d %d %d", &u, &v, &l);
        mask = 0;
        while (l-- > 0)
        {
            scanf("%d", &t);
            if (t >= 1 && t <= 63)
                mask |= 1ULL << t;
        }
        if (u >= 1 && u <= n && v >= 1 && v <= n)
        {
            eu[cnt] = u;
            ev[cnt] = v;
            emask[cnt] = mask;
            cnt++;
        }
    }
    m = cnt;

    /* every token is allowed: if this fails, it is impossible */
    allowed = (k >= 63) ? ~0ULL : ((1ULL << (k + 1)) - 2);
    if (!connected(n, m, allowed))
    {
        printf("-1\n");
        return 0;
    }

    for (i = k; i >= 1; i--)
    {
        /* bits 1..i-1 are the cheaper tokens */
        allowed = chosen | ((1ULL << i) - 2);
        if (!connected(n, m, allowed))
        {
            chosen |= 1ULL << i;
            cost += c[i];
        }
    }
    printf("%llu\n", cost);
    return 0;
}
