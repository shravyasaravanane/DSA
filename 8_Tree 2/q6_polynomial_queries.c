/*
 * Tree 2 - Polynomial queries (Challenge 76)
 * Array of n values, two kinds of queries:
 *   1 a b : increase the first value of [a,b] by 1, the second by 2, the
 *           third by 3, and so on
 *   2 a b : print the sum of the values in [a,b]
 *
 * Idea: segment tree with lazy propagation of an arithmetic progression.
 * A pending update of a node is stored as (A, D): position l+j of the node
 * (j = 0, 1, ...) has to be increased by A + j*D. Two pending updates simply
 * add up (A1+A2, D1+D2). For a node of length len the sum grows by
 *   A*len + D*len*(len-1)/2.
 * When pushing to the children the right child starts at A + D*(len of the
 * left child). Every query costs O(log n).
 * (Any type other than 1 is treated as a sum query, like the eLab sample
 *  "3 2 3"; a right end beyond n is cut to n.)
 *
 * Input : n q, the n values, then q queries.
 * Output: the answer of every sum query.
 *
 * Sample: 5 3 / 4 2 3 1 7 / 2 1 5 / 1 1 5 / 2 1 5 -> 17 32
 */
#include <stdio.h>

#define MAXN 200005

long long a[MAXN];
long long sum[4 * MAXN], lzA[4 * MAXN], lzD[4 * MAXN];

void build(int k,int l,int r)
{
    int mid;
    lzA[k] = lzD[k] = 0;
    if (l == r)
    {
        sum[k] = a[l];
        return;
    }
    mid = (l + r) / 2;
    build(2 * k, l, mid);
    build(2 * k + 1, mid + 1, r);
    sum[k] = sum[2 * k] + sum[2 * k + 1];
}

/* adds first + j*step to the j-th element of the node range [l, r] */
void apply(int k, int l, int r, long long first, long long step)
{
    long long len = r - l + 1;
    sum[k] += first * len + step * len * (len - 1) / 2;
    lzA[k] += first;
    lzD[k] += step;
}

void push(int k, int l, int r)
{
    int mid;
    if (lzA[k] == 0 && lzD[k] == 0)
        return;
    mid = (l + r) / 2;
    apply(2 * k, l, mid, lzA[k], lzD[k]);
    apply(2 * k + 1, mid + 1, r, lzA[k] + lzD[k] * (mid + 1 - l), lzD[k]);
    lzA[k] = lzD[k] = 0;
}

void update(int k, int l, int r, int ql, int qr)
{
    int mid;
    if (qr < l || r < ql)
        return;
    if (ql <= l && r <= qr)
    {
        apply(k, l, r, l - ql + 1, 1);
        return;
    }
    push(k, l, r);
    mid = (l + r) / 2;
    update(2 * k, l, mid, ql, qr);
    update(2 * k + 1, mid + 1, r, ql, qr);
    sum[k] = sum[2 * k] + sum[2 * k + 1];
}

long long query(int k, int l, int r, int ql, int qr)
{
    int mid;
    if (qr < l || r < ql)
        return 0;
    if (ql <= l && r <= qr)
        return sum[k];
    push(k, l, r);
    mid = (l + r) / 2;
    return query(2 * k, l, mid, ql, qr) + query(2 * k + 1, mid + 1, r, ql, qr);
}

int main()
{
    int n, q, i, t, x, y;

    scanf("%d %d", &n, &q);
    for (i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    build(1, 1, n);

    while (q-- > 0)
    {
        scanf("%d %d %d", &t, &x, &y);
        if (y > n)
            y = n;
        if (t == 1)
        {
            if (x <= y)
                update(1, 1, n, x, y);
        }
        else if (x <= y)
            printf("%lld\n", query(1, 1, n, x, y));
        else
            printf("0\n");
    }
    return 0;
}
