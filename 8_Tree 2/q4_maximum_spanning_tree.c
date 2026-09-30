/*
 * Tree 2 - Maximum spanning tree (Challenge 74)
 * Weighted undirected graph with N vertices and M edges. Print the total
 * weight of its MAXIMUM spanning tree.
 *
 * Idea: Prim's algorithm with a binary max-heap.
 *   - start from a vertex, put all its edges into the heap,
 *   - repeatedly take the heaviest edge; if it leads to a vertex that is not
 *     in the tree yet, add the vertex, add the weight and push its edges.
 * printheap(N) runs the algorithm on the graph that was read and returns the
 * total weight (if the graph were not connected it gives the weight of the
 * maximum spanning forest). Time O(M log M).
 *
 * Input : T, then for every test: N M and M lines "a b c".
 * Output: the weight of the maximum spanning tree for every test.
 *
 * Sample: 1 / 3 3 / 1 2 2 / 2 3 3 / 1 3 4 -> 7
 *         1 / 3 3 / 1 2 3 / 2 3 4 / 1 3 5 -> 9
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXN 5005
#define MAXM 100005

struct edge
{
    int w, v;
};

int head[MAXN], nxt[2 * MAXM], to[2 * MAXM], wt[2 * MAXM], ecnt;
int visited[MAXN];
struct edge heap[2 * MAXM];
int hsize;

void addEdge(int u, int v, int w)
{
    to[ecnt] = v;
    wt[ecnt] = w;
    nxt[ecnt] = head[u];
    head[u] = ecnt++;
}

void heapPush(int w, int v)
{
    int i = hsize++;
    struct edge t;
    heap[i].w = w;
    heap[i].v = v;
    while (i > 0 && heap[i].w > heap[(i - 1) / 2].w)
    {
        int p = (i - 1) / 2;
        t = heap[i];
        heap[i] = heap[p];
        heap[p] = t;
        i = p;
    }
}

struct edge heapPop()
{
    struct edge top = heap[0], t;
    int i = 0, c;
    heap[0] = heap[--hsize];
    while (1)
    {
        c = 2 * i + 1;
        if (c >= hsize)
            break;
        if (c + 1 < hsize && heap[c + 1].w > heap[c].w)
            c++;
        if (heap[c].w <= heap[i].w)
            break;
        t = heap[i];
        heap[i] = heap[c];
        heap[c] = t;
        i = c;
    }
    return top;
}

int printheap(int N)
{
    int s, e, total = 0;
    struct edge cur;

    for (s = 1; s <= N; s++)
        visited[s] = 0;

    for (s = 1; s <= N; s++)
    {
        if (visited[s])
            continue;
        visited[s] = 1;
        hsize = 0;
        for (e = head[s]; e != -1; e = nxt[e])
            heapPush(wt[e], to[e]);
        while (hsize > 0)
        {
            cur = heapPop();
            if (visited[cur.v])
                continue;
            visited[cur.v] = 1;
            total += cur.w;
            for (e = head[cur.v]; e != -1; e = nxt[e])
                if (!visited[to[e]])
                    heapPush(wt[e], to[e]);
        }
    }
    return total;
}

int main()
{
    int t, n, m, i, a, b, c;

    scanf("%d", &t);
    while (t-- > 0)
    {
        scanf("%d %d", &n, &m);
        ecnt = 0;
        for (i = 1; i <= n; i++)
            head[i] = -1;
        for (i = 0; i < m; i++)
        {
            scanf("%d %d %d", &a, &b, &c);
            addEdge(a, b, c);
            addEdge(b, a, c);
        }
        printf("%d\n", printheap(n));
    }
    return 0;
}
