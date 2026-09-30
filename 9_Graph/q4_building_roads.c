/*
 * Graph - Byteland, connect all the cities (Challenge 84)
 * Find the minimum number of new roads that make the whole graph connected
 * and print the roads.
 * The cities form several connected components (found with a DSU). k
 * components need exactly k-1 new roads: link the first component with
 * every other one, using each component's DSU representative.
 *
 * Input : n m, then m lines "a b".
 * Output: k, then k lines with the new roads.
 *
 * Sample: 4 2 / 1 2 / 3 4  ->  1 / 2 4
 *         4 2 / 2 3 / 2 4  ->  1 / 1 4
 */
#include <stdio.h>

#define MAXN 100005

int parent[MAXN];
int root[MAXN];

int find(int x)
{
    while (parent[x] != x)
    {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

int main()
{
    int n, m, a, b, i, cnt = 0;

    scanf("%d %d", &n, &m);
    for (i = 1; i <= n; i++)
        parent[i] = i;

    while(m--)
    {
        scanf("%d %d", &a, &b);
        a = find(a);
        b = find(b);
        if (a != b)
            parent[a] = b;
    }

    /* one representative per component, in increasing order */
    for (i = 1; i <= n; i++)
        if (find(i) == i)
            root[cnt++] = i;

    printf("%d\n", cnt - 1);
    for (i = 1; i < cnt; i++)
        printf("%d %d\n", root[0], root[i]);
    return 0;
}
