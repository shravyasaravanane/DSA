/*
 * Tree 2 - Replace the greatest and smallest by their difference (Challenge 72)
 * One operation removes the greatest and the smallest element of the array
 * and inserts their difference. For every query K print the sum of the array
 * after K operations.
 *
 * Idea: simulate all N-1 operations once and remember the sum after each
 * step, ans[K]; then every query is answered in O(1).
 * To get the maximum and the minimum quickly two binary heaps are used
 * (a max-heap and a min-heap of element ids). An element removed from one
 * heap is only marked as dead and is skipped when it reaches the top of the
 * other heap (lazy deletion). Total time O(N log N).
 *   sum after step = sum - max - min + (max - min)
 *
 * Input : N Q, the N elements, then Q lines with K.
 * Output: the sum after K operations, one line per query.
 *
 * Sample: 5 2 / 3 2 1 5 4 / 1 / 2 -> 13 9
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005

long long val[MAXN];
int alive[MAXN];
int hmax[MAXN], hmin[MAXN], szmax = 0, szmin = 0;
long long ans[MAXN];

/* better(a, b): 1 if element a must be above element b in the heap of 'mode' */
int better(int a, int b, int mode)
{
    return mode == 0 ? val[a] > val[b] : val[a] < val[b];
}

void push(int *h, int *sz, int id, int mode)
{
    int i = (*sz)++;
    h[i] = id;
    while (i > 0 && better(h[i], h[(i - 1) / 2], mode))
    {
        int p = (i - 1) / 2, t = h[i];
        h[i] = h[p];
        h[p] = t;
        i = p;
    }
}

void pop(int *h, int *sz, int mode)
{
    int i = 0, c, t;
    h[0] = h[--(*sz)];
    while (1)
    {
        c = 2 * i + 1;
        if (c >= *sz)
            break;
        if (c + 1 < *sz && better(h[c + 1], h[c], mode))
            c++;
        if (!better(h[c], h[i], mode))
            break;
        t = h[i];
        h[i] = h[c];
        h[c] = t;
        i = c;
    }
}

/* top alive element of a heap, dead ones are discarded */
int topAlive(int *h, int *sz, int mode)
{
    while (*sz > 0 && !alive[h[0]])
        pop(h, sz, mode);
    return h[0];
}

int main()
{
    int n, q, i, k, mx, mn, cnt;
    long long sum = 0, d;

    scanf("%d %d", &n, &q);
    for(i=0;i<n;i++)
    {
        scanf("%lld", &val[i]);
        alive[i] = 1;
        sum += val[i];
        push(hmax, &szmax, i, 0);
        push(hmin, &szmin, i, 1);
    }
    cnt = n;
    ans[0] = sum;

    for (k = 1; k < n; k++)
    {
        mx = topAlive(hmax, &szmax, 0);
        alive[mx] = 0;
        mn = topAlive(hmin, &szmin, 1);
        alive[mn] = 0;
        d = val[mx] - val[mn];
        val[cnt] = d;
        alive[cnt] = 1;
        push(hmax, &szmax, cnt, 0);
        push(hmin, &szmin, cnt, 1);
        cnt++;
        sum = sum - val[mx] - val[mn] + d;
        ans[k] = sum;
    }

    while (q-- > 0)
    {
        scanf("%d", &k);
        printf("%lld\n", ans[k]);
    }
    return 0;
}
