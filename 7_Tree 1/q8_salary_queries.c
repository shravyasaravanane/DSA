/*
 * Tree 1 - Salary queries (Challenge 68)
 * n salaries and q queries of two kinds:
 *   ! k x : change the salary of employee k to x
 *   ? a b : count the employees whose salary is in the range a..b
 *
 * Idea: offline coordinate compression + Fenwick (binary indexed) tree.
 *  1. read everything, collect every salary value that can ever appear
 *     (initial salaries, new salaries, query bounds) and sort them with
 *     qsort() using compare(); remove duplicates,
 *  2. the Fenwick tree stores how many employees have each compressed value,
 *  3. an update is two point updates (-1 old value, +1 new value),
 *     a query is  prefix(b) - prefix(a-1).
 * Every operation costs O(log(n + q)).
 *
 * Input : n q, the n salaries, then q queries.
 * Output: the answer of every ? query.
 *
 * Sample: 5 3 / 3 7 2 2 5 / ? 2 3 / ! 3 6 / ? 2 3 -> 3 2
 */
#include <stdio.h>
#include <stdlib.h>

int compare(const void *a,const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

int *bit;

/* adds x at position i of a Fenwick tree of size n */
void update(int i,int n,int x)
{
    for (; i <= n; i += i & (-i))
        bit[i] += x;
}

int prefix(int i)
{
    int s = 0;
    for (; i > 0; i -= i & (-i))
        s += bit[i];
    return s;
}

/* position (1-based) of value v in the sorted distinct array vals[0..m-1] */
int position(int *vals, int m, int v)
{
    int lo = 0, hi = m - 1, mid;
    while (lo <= hi)
    {
        mid = (lo + hi) / 2;
        if (vals[mid] == v)
            return mid + 1;
        if (vals[mid] < v)
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    return 0;
}

int main()
{
    int n, q, i, m, total = 0;
    int *sal, *vals, *qa, *qb;
    char *qt;
    char ch;

    scanf("%d %d", &n, &q);
    sal  = (int *)malloc((n + 1) * sizeof(int));
    vals = (int *)malloc((n + 2 * q + 1) * sizeof(int));
    qa   = (int *)malloc((q + 1) * sizeof(int));
    qb   = (int *)malloc((q + 1) * sizeof(int));
    qt   = (char *)malloc(q + 1);

    for (i = 1; i <= n; i++)
    {
        scanf("%d", &sal[i]);
        vals[total++] = sal[i];
    }
    for (i = 0; i < q; i++)
    {
        scanf(" %c %d %d", &ch, &qa[i], &qb[i]);
        qt[i] = ch;
        if (ch == '!')
            vals[total++] = qb[i];
        else
        {
            vals[total++] = qa[i];
            vals[total++] = qb[i];
        }
    }

    qsort(vals, total, sizeof(int), compare);
    m = 0;
    for (i = 0; i < total; i++)
        if (i == 0 || vals[i] != vals[i - 1])
            vals[m++] = vals[i];

    bit = (int *)calloc(m + 2, sizeof(int));
    for (i = 1; i <= n; i++)
        update(position(vals, m, sal[i]), m, 1);

    for (i = 0; i < q; i++)
    {
        if (qt[i] == '!')
        {
            update(position(vals, m, sal[qa[i]]), m, -1);
            sal[qa[i]] = qb[i];
            update(position(vals, m, sal[qa[i]]), m, 1);
        }
        else if (qa[i] > qb[i])
            printf("0\n");
        else
            printf("%d\n", prefix(position(vals, m, qb[i]))
                           - prefix(position(vals, m, qa[i]) - 1));
    }
    return 0;
}
