/*
 * Hashing - Set index and find the next set index (Challenge 98)
 * Array of length N (up to 10^9, all zeros). Queries:
 *   1 k : set A[k] = 1
 *   2 y : print the smallest index x >= y with A[x] = 1, or -1
 * N is far too big for an array, but only the Q indices used by type 1
 * queries matter. Offline solution:
 *   1. sort the distinct indices of all type 1 queries (keys);
 *   2. answer the queries in REVERSE order, starting with every key set;
 *      going backwards a "set" query undoes a set (only the first time an
 *      index was set), and a DSU "next active key" structure supports
 *      deleting a key by linking it to the next one;
 *   3. a type 2 query jumps to the first key >= y (binary search) and asks
 *      the DSU for the next key that is still active at that moment.
 * Complexity O(Q log Q).
 *
 * Input : N Q, then Q lines "type value".  Output: one line per type 2.
 *
 * Sample: 5 5 / 2 3 / 1 2 / 2 1 / 2 3 / 2 2  ->  -1 / 2 / -1 / 2
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXQ 500005

int type[MAXQ], val[MAXQ], keys[MAXQ], pos[MAXQ], nxt[MAXQ + 1], ans[MAXQ];
char first[MAXQ], seen[MAXQ];

int cmp(const void *a, const void *b)
{
    return *(const int *)a - *(const int *)b;
}

/* first position in keys[0..m) with keys[p] >= v */
int lowerBound(int m, int v)
{
    int lo = 0, hi = m, mid;
    while (lo < hi)
    {
        mid = (lo + hi) / 2;
        if (keys[mid] < v)
            lo = mid + 1;
        else
            hi = mid;
    }
    return lo;
}

int find(int x)
{
    while (nxt[x] != x)
    {
        nxt[x] = nxt[nxt[x]];
        x = nxt[x];
    }
    return x;
}

int main()
{
    int n, q, i, m = 0, cnt = 0, r;

    scanf("%d %d", &n, &q);
    for(i=0;i<q;i++)
    {
        scanf("%d %d", &type[i], &val[i]);
        if (type[i] == 1)
            keys[cnt++] = val[i];
    }

    qsort(keys, cnt, sizeof(int), cmp);
    for (i = 0; i < cnt; i++)
        if (i == 0 || keys[i] != keys[i - 1])
            keys[m++] = keys[i];

    /* position of every query value in the key list */
    for (i = 0; i < q; i++)
    {
        pos[i] = lowerBound(m, val[i]);
        if (type[i] == 1 && !seen[pos[i]])
        {
            seen[pos[i]] = 1;
            first[i] = 1;          /* first time this index is set */
        }
    }

    for (i = 0; i <= m; i++)
        nxt[i] = i;                /* every key is active at the end */

    for (i = q - 1; i >= 0; i--)
    {
        if (type[i] == 1)
        {
            if (first[i])
                nxt[pos[i]] = pos[i] + 1;      /* undo: key not set yet */
        }
        else
        {
            r = find(pos[i]);
            ans[i] = (r == m) ? -1 : keys[r];
        }
    }

    for (i = 0; i < q; i++)
        if (type[i] == 2)
            printf("%d\n", ans[i]);
    return 0;
}
