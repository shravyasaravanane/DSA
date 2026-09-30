/*
 * Graph - Roads built day by day (Challenge 87)
 * After every new road print the number of components and the size of the
 * largest component -> Disjoint Set Union (union by size, path compression).
 * join(i,j) merges the two components and returns 1 if they were different.
 *
 * Input : n m, then m lines "a b".
 * Output: m lines "components largest".
 *
 * Sample: 5 6 / 1 2 / 2 3 / 3 1 / 3 4 / 4 5 / 5 4
 *         -> 4 2 / 3 3 / 3 3 / 2 4 / 1 5 / 1 5
 */
#include <stdio.h>

#define MAXN 100005

int parent[MAXN], size[MAXN];

int find(int x)
{
    while (parent[x] != x)
    {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

int join(int i,int j)
{
    int t;
    i = find(i);
    j = find(j);
    if (i == j)
        return 0;
    if (size[i] < size[j])
    {
        t = i;
        i = j;
        j = t;
    }
    parent[j] = i;
    size[i] += size[j];
    return 1;
}

int main()
{
    int n, m, a, b, i, comps, best = 1;

    scanf("%d %d", &n, &m);
    for (i = 1; i <= n; i++)
    {
        parent[i] = i;
        size[i] = 1;
    }
    comps = n;

    for (i = 0; i < m; i++)
    {
        scanf("%d %d", &a, &b);
        if (join(a, b))
        {
            comps--;
            if (size[find(a)] > best)
                best = size[find(a)];
        }
        printf("%d %d\n", comps, best);
    }
    return 0;
}
