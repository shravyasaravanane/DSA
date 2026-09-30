/*
 * Graph - Maximum matching in a tree (Challenge 88)
 * A matching is a set of edges where every node is used at most once.
 * Greedy from the leaves: a node that is still free after all its children
 * were handled is matched with its parent if the parent is free too. This is
 * optimal for trees (a leaf can only be matched with its parent, so taking
 * that edge never hurts).
 * dfs(p,i) is an iterative depth first search (no recursion, n up to 2*10^5)
 * that records the parent of every node and the visiting order; walking the
 * order backwards processes every child before its parent.
 *
 * Input : n, then n-1 lines "a b".      Output: the size of a maximum matching.
 *
 * Sample: 5 / 1 2 / 1 3 / 3 4 / 3 5  ->  2
 */
#include <stdio.h>

#define MAXN 200005

int head[MAXN], nxt[2 * MAXN], to[2 * MAXN], ec = 0;
int par[MAXN], order[MAXN], seen[MAXN], cur[MAXN], matched[MAXN];
int cnt = 0;

/* undirected edge i - j */
void link(int i,int j)
{
    ec++;
    to[ec] = j;
    nxt[ec] = head[i];
    head[i] = ec;
    ec++;
    to[ec] = i;
    nxt[ec] = head[j];
    head[j] = ec;
}

/* visit the tree of node i, whose parent is p (0 for a root) */
void dfs(int p,int i)
{
    static int stack[MAXN];
    int top = 0, u, v, e;
    par[i] = p;
    seen[i] = 1;
    order[cnt++] = i;
    cur[i] = head[i];
    stack[top++] = i;
    while (top > 0)
    {
        u = stack[top - 1];
        e = cur[u];
        if (e == 0)
        {
            top--;
            continue;
        }
        cur[u] = nxt[e];
        v = to[e];
        if (!seen[v])
        {
            seen[v] = 1;
            par[v] = u;
            order[cnt++] = v;
            cur[v] = head[v];
            stack[top++] = v;
        }
    }
}

int main()
{
    int n, a, b, i, v, ans = 0;

    scanf("%d", &n);
    for (i = 1; i < n; i++)
    {
        scanf("%d %d", &a, &b);
        link(a, b);
    }

    for (i = 1; i <= n; i++)
        if (!seen[i])
            dfs(0, i);

    for (i = cnt - 1; i >= 0; i--)
    {
        v = order[i];
        if (par[v] && !matched[v] && !matched[par[v]])
        {
            matched[v] = matched[par[v]] = 1;
            ans++;
        }
    }
    printf("%d\n", ans);
    return 0;
}
