/*
 * Graph - "good" graph where every simple cycle has XOR weight 1 (Ch 85)
 * Edges (u v x) arrive one by one; an edge is added only if the graph stays
 * good.
 *
 * Facts (x is 0/1):
 *   - If two cycles share an edge, take the three paths a, b, c between the
 *     branch points: a^b = b^c = a^c = 1 is impossible. So every edge may lie
 *     on at most ONE cycle (the graph is a cactus).
 *   - Then every simple cycle is one of those cycles, so each must have XOR 1.
 * An edge whose ends are in different components is always added (it joins
 * two trees). Otherwise it closes a cycle with the unique tree path u..v:
 *   * that path must contain no tree edge that already lies on a cycle,
 *   * xor(path) ^ x must be 1.
 * If it is accepted, the tree edges of the path become "used".
 *
 * Offline trick: whether an edge joins two components does not depend on
 * rejected edges, so the final spanning forest is built first with a DSU.
 * dfs1 (iterative) gives tin/tout, depth, xor-to-root and the ancestors for
 * LCA. A Fenwick tree counts used tree edges on a root path (marking the
 * edge to child c adds 1 on the whole subtree of c).
 *
 * Input : n q, then q lines "u v x".      Output: YES / NO for every query.
 *
 * Sample: 9 6 / 1 3 1 / 3 6 0 / 6 4 1 / 2 4 0 / 4 5 0 / 7 8 1 -> 6 x YES
 */
#include <stdio.h>

#define MAXN 300005
#define MAXQ 500005
#define LOG 19

int head[MAXN], nxt[2 * MAXN], to[2 * MAXN], wt[2 * MAXN], ec = 0;
int up[LOG][MAXN], depth[MAXN], xr[MAXN], tin[MAXN], tout[MAXN];
int cur[MAXN], seen[MAXN], stk[MAXN], bit[MAXN + 2];
int dsu[MAXN];
int qu[MAXQ], qv[MAXQ], qx[MAXQ], istree[MAXQ];
int timer = 0, n;

int find(int x)
{
    while (dsu[x] != x)
    {
        dsu[x] = dsu[dsu[x]];
        x = dsu[x];
    }
    return x;
}

void addEdge(int a,int b,int w)
{
    ec++;
    to[ec] = b;
    wt[ec] = w;
    nxt[ec] = head[a];
    head[a] = ec;
}

/* iterative dfs of the tree that contains np; lst is the parent of np */
int dfs1(int np,int lst)
{
    int top = 0, u, v, e;
    up[0][np] = lst ? lst : np;
    depth[np] = 0;
    xr[np] = 0;
    seen[np] = 1;
    tin[np] = ++timer;
    cur[np] = head[np];
    stk[top++] = np;
    while (top > 0)
    {
        u = stk[top - 1];
        e = cur[u];
        if (e)
        {
            cur[u] = nxt[e];
            v = to[e];
            if (!seen[v])
            {
                seen[v] = 1;
                up[0][v] = u;
                depth[v] = depth[u] + 1;
                xr[v] = xr[u] ^ wt[e];
                tin[v] = ++timer;
                cur[v] = head[v];
                stk[top++] = v;
            }
        }
        else
        {
            tout[u] = timer;
            top--;
        }
    }
    return timer;
}

void add(int i,int d)
{
    for (; i <= n + 1; i += i & -i)
        bit[i] += d;
}

int sum(int i)
{
    int s = 0;
    for (; i > 0; i -= i & -i)
        s += bit[i];
    return s;
}

/* number of used tree edges on the path root .. v */
int used(int v)
{
    return sum(tin[v]);
}

/* the tree edge (parent of c, c) becomes used */
void mark(int c)
{
    add(tin[c], 1);
    add(tout[c] + 1, -1);
}

int lca(int u,int v)
{
    int j, t;
    if (depth[u] < depth[v])
    {
        t = u;
        u = v;
        v = t;
    }
    for (j = LOG - 1; j >= 0; j--)
        if (depth[u] - (1 << j) >= depth[v])
            u = up[j][u];
    if (u == v)
        return u;
    for (j = LOG - 1; j >= 0; j--)
        if (up[j][u] != up[j][v])
        {
            u = up[j][u];
            v = up[j][v];
        }
    return up[0][u];
}

int main()
{
    int q, i, j, u, v, x, a, b, l;

    scanf("%d %d", &n, &q);
    for (i = 1; i <= n; i++)
        dsu[i] = i;

    /* spanning forest of the whole input */
    for (i = 0; i < q; i++)
    {
        scanf("%d %d %d", &qu[i], &qv[i], &qx[i]);
        a = find(qu[i]);
        b = find(qv[i]);
        if (a != b)
        {
            dsu[a] = b;
            istree[i] = 1;
            addEdge(qu[i], qv[i], qx[i]);
            addEdge(qv[i], qu[i], qx[i]);
        }
    }

    for (i = 1; i <= n; i++)
        if (!seen[i])
            dfs1(i, 0);

    for (j = 1; j < LOG; j++)
        for (i = 1; i <= n; i++)
            up[j][i] = up[j - 1][up[j - 1][i]];

    for (i = 0; i < q; i++)
    {
        if (istree[i])
        {
            puts("YES");
            continue;
        }
        u = qu[i];
        v = qv[i];
        x = qx[i];
        l = lca(u, v);
        if ((xr[u] ^ xr[v] ^ x) == 1 && used(u) + used(v) - 2 * used(l) == 0)
        {
            puts("YES");
            for (a = u; a != l; a = up[0][a])
                mark(a);
            for (a = v; a != l; a = up[0][a])
                mark(a);
        }
        else
            puts("NO");
    }
    return 0;
}
