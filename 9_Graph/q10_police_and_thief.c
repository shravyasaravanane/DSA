/*
 * Graph - Kaaleppi and the police (Challenge 90)  ->  minimum cut
 * Close the minimum number of two-way streets so that crossing 1 (bank) and
 * crossing n (harbor) are disconnected. Every street has capacity 1 in both
 * directions, so by max-flow = min-cut the answer is the maximum flow
 * (Edmonds-Karp, bfs finds the shortest augmenting path).
 * After the flow, the crossings still reachable from 1 in the residual graph
 * form the source side S (the last failed bfs marks them). The streets that
 * go from S to the other side are exactly a minimum cut.
 *
 * Input : n m, then m lines "a b".
 * Output: k, then k lines "a b" with the streets to close.
 *
 * Sample: 4 5 / 1 2 / 1 3 / 2 3 / 3 4 / 1 4  ->  2 / 1 4 / 3 4
 */
#include <stdio.h>

#define MAXV 100005
#define MAXE 400010

int head[MAXV], nxt[MAXE], to[MAXE], cap[MAXE], ec = 2;
int prevE[MAXV], vis[MAXV], q[MAXV];

/* two-way street i - h: both arcs have capacity 1 and reverse each other */
void link(int i,int h)
{
    to[ec] = h;
    cap[ec] = 1;
    nxt[ec] = head[i];
    head[i] = ec;
    to[ec + 1] = i;
    cap[ec + 1] = 1;
    nxt[ec + 1] = head[h];
    head[h] = ec + 1;
    ec += 2;
}

/* breadth first search in the residual graph, 1 if t can be reached */
int bfs(int n,int s,int t)
{
    int i, u, v, e, front = 0, back = 0;
    for (i = 1; i <= n; i++)
        vis[i] = 0;
    vis[s] = 1;
    q[back++] = s;
    while (front < back)
    {
        u = q[front++];
        for (e = head[u]; e; e = nxt[e])
        {
            v = to[e];
            if (cap[e] > 0 && !vis[v])
            {
                vis[v] = 1;
                prevE[v] = e;
                q[back++] = v;
            }
        }
    }
    return vis[t];
}

int main()
{
    int n, m, a, b, i, v, e, flow = 0;

    scanf("%d %d", &n, &m);
    for (i = 0; i < m; i++)
    {
        scanf("%d %d", &a, &b);
        if (a != b && a >= 1 && a <= n && b >= 1 && b <= n)
            link(a, b);
    }

    while (bfs(n, 1, n))
    {
        v = n;
        while (v != 1)
        {
            e = prevE[v];
            cap[e]--;
            cap[e ^ 1]++;
            v = to[e ^ 1];
        }
        flow++;
    }

    /* vis[] now holds the crossings reachable from 1 */
    printf("%d\n", flow);
    for (i = 1; i <= n; i++)
    {
        if (!vis[i])
            continue;
        for (e = head[i]; e; e = nxt[e])
            if (!vis[to[e]])
                printf("%d %d\n", i, to[e]);
    }
    return 0;
}
