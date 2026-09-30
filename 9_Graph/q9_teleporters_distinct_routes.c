/*
 * Graph - Teleporters game, maximum number of days (Challenge 89)
 * n rooms, m one-way teleporters, every teleporter can be used at most once
 * in the whole game and every day starts in room 1 and must end in room n.
 * => the answer is the maximum number of edge-disjoint paths from 1 to n,
 *    i.e. a maximum flow with capacity 1 on every teleporter.
 *
 * Algorithm (Edmonds-Karp): bfs(n,s,t) finds a shortest augmenting path in
 * the residual graph; every augmentation sends one unit. The graph is kept
 * as linked lists (link adds an arc and its reverse arc).
 * After the flow, the paths are read back by walking along arcs that carry
 * flow from room 1; if a walk enters a room twice, the loop is dropped.
 *
 * Input : n m, then m lines "a b".
 * Output: k, then for every day: the number of rooms and the rooms.
 *
 * Sample: 6 7 / 1 2 / 1 3 / 2 6 / 3 4 / 3 5 / 4 6 / 5 6
 *         -> 2 / 4 / 1 3 5 6 / 3 / 1 2 6
 */
#include <stdio.h>

#define MAXV 100005
#define MAXE 400010

int head[MAXV], nxt[MAXE], to[MAXE], cap[MAXE], ec = 2;
int prevE[MAXV], vis[MAXV], q[MAXV];
int cp[MAXV], pos[MAXV], path[MAXV];

/* arc a->b (capacity 1) and its reverse arc b->a (capacity 0) */
void link(int a,int b)
{
    to[ec] = b;
    cap[ec] = 1;
    nxt[ec] = head[a];
    head[a] = ec;
    to[ec + 1] = a;
    cap[ec + 1] = 0;
    nxt[ec + 1] = head[b];
    head[b] = ec + 1;
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
    while (front < back && !vis[t])
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
    int n, m, a, b, i, v, e, k = 0, len, x;

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
        k++;
    }

    for (i = 1; i <= n; i++)
    {
        cp[i] = head[i];
        pos[i] = -1;
    }

    printf("%d\n", k);
    for (i = 0; i < k; i++)
    {
        len = 0;
        path[len] = 1;
        pos[1] = len++;
        v = 1;
        while (v != n)
        {
            /* next unused arc that carries flow (original arcs are even) */
            while (cp[v] && !((cp[v] & 1) == 0 && cap[cp[v]] == 0))
                cp[v] = nxt[cp[v]];
            e = cp[v];
            cp[v] = nxt[e];
            v = to[e];
            if (pos[v] != -1)
            {
                /* a loop: go back to the earlier visit of v */
                while (path[len - 1] != v)
                    pos[path[--len]] = -1;
            }
            else
            {
                path[len] = v;
                pos[v] = len++;
            }
        }
        printf("%d\n", len);
        for (x = 0; x < len; x++)
        {
            printf("%d", path[x]);
            printf(x + 1 < len ? " " : "\n");
            pos[path[x]] = -1;
        }
    }
    return 0;
}
