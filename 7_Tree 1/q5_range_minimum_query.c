/*
 * Tree 1 - Range minimum queries (Challenge 65)
 * Array of n integers, q queries "a b": minimum value in positions a..b.
 *
 * Idea: segment tree. Node k covers the range [l, r]; tree[k] stores the
 * minimum of that range.
 *   build : O(n)          query : O(log n)
 * A query range that does not overlap a node returns INT_MAX, a range that
 * fully covers the node returns tree[k], otherwise both children are asked.
 *
 * Input : n q, the n values, then q lines "a b" (1-based).
 * Output: the minimum of every query.
 *
 * Sample: 8 4 / 3 2 4 5 1 1 5 3 / 2 4 / 5 6 / 1 8 / 3 3 -> 2 1 1 4
 */
#include <stdio.h>
#include <limits.h>

#define MAXN 200005

int aa[MAXN];
int tree[4 * MAXN];

int min(int a, int b)
{
    return a < b ? a : b;
}

void build(int *aa,int k,int l,int r)
{
    int mid;
    if (l == r)
    {
        tree[k] = aa[l];
        return;
    }
    mid = (l + r) / 2;
    build(aa, 2 * k, l, mid);
    build(aa, 2 * k + 1, mid + 1, r);
    tree[k] = min(tree[2 * k], tree[2 * k + 1]);
}

int query(int k,int l,int r,int ql,int qr)
{
    int mid;
    if (qr < l || r < ql)
        return INT_MAX;
    if (ql <= l && r <= qr)
        return tree[k];
    mid = (l + r) / 2;
    return min(query(2 * k, l, mid, ql, qr),
               query(2 * k + 1, mid + 1, r, ql, qr));
}

int main()
{
    int n, q, i, a, b;

    scanf("%d %d", &n, &q);
    for (i = 1; i <= n; i++)
        scanf("%d", &aa[i]);

    build(aa, 1, 1, n);

    while (q-- > 0)
    {
        scanf("%d %d", &a, &b);
        printf("%d\n", query(1, 1, n, a, b));
    }
    return 0;
}
