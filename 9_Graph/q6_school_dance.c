/*
 * Graph - School dance, maximum number of pairs (Challenge 86)
 * Boys and girls form a bipartite graph (an edge = the pair is willing to
 * dance). The answer is a maximum bipartite matching.
 *
 * Algorithm: Hopcroft-Karp.
 *   bfs(n)  : layers the boys starting from the free ones and reports whether
 *             a free girl can be reached (an augmenting path exists);
 *   dfs(u)  : follows only the layered edges and augments along the path.
 * Phases repeat until bfs finds no augmenting path. The graph is stored as
 * linked lists (link adds an edge).
 *
 * Input : n m k, then k lines "a b" (boy a, girl b).
 * Output: the number of pairs and then the pairs "boy girl" (by boy number).
 *
 * Sample: 3 2 4 / 1 1 / 1 2 / 2 1 / 3 1  ->  2 / 1 2 / 2 1
 */
#include <stdio.h>

#define MAXV 100005
#define MAXE 200005

int head[MAXV], nxt[MAXE], to[MAXE], ec = 0;
int matchL[MAXV], matchR[MAXV], dist[MAXV], q[MAXV];

/* boy u is willing to dance with girl v */
void link(int u,int v)
{
    ec++;
    to[ec] = v;
    nxt[ec] = head[u];
    head[u] = ec;
}

/* layer the boys; returns 1 if an augmenting path exists */
int bfs(int n)
{
    int u, v, w, e, front = 0, back = 0, found = 0;
    for (u = 1; u <= n; u++)
    {
        if (matchL[u] == 0)
        {
            dist[u] = 0;
            q[back++] = u;
        }
        else
            dist[u] = -1;
    }
    while (front < back)
    {
        u = q[front++];
        for (e = head[u]; e; e = nxt[e])
        {
            v = to[e];
            w = matchR[v];
            if (w == 0)
                found = 1;
            else if (dist[w] < 0)
            {
                dist[w] = dist[u] + 1;
                q[back++] = w;
            }
        }
    }
    return found;
}

int dfs(int u)
{
    int e, v, w;
    for (e = head[u]; e; e = nxt[e])
    {
        v = to[e];
        w = matchR[v];
        if (w == 0 || (dist[w] == dist[u] + 1 && dfs(w)))
        {
            matchL[u] = v;
            matchR[v] = u;
            return 1;
        }
    }
    dist[u] = -1;
    return 0;
}

int main()
{
    int n, m, k, a, b, i, res = 0;

    scanf("%d %d %d", &n, &m, &k);
    for (i = 0; i < k; i++)
    {
        scanf("%d %d", &a, &b);
        if (a >= 1 && a <= n && b >= 1 && b < MAXV)
            link(a, b);
    }

    while (bfs(n))
        for (i = 1; i <= n; i++)
            if (matchL[i] == 0 && dfs(i))
                res++;

    printf("%d\n", res);
    for (i = 1; i <= n; i++)
        if (matchL[i])
            printf("%d %d\n", i, matchL[i]);
    return 0;
}
