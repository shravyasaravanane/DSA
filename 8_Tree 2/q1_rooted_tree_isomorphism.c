/*
 * Tree 2 - Tree isomorphism (Challenge 71)
 * Two rooted trees (root = node 1) with n nodes are isomorphic when one can
 * be drawn exactly like the other, i.e. the children of a node can be
 * reordered so that both trees look the same.
 *
 * Idea (canonical ids, AHU algorithm):
 *   - give every node an id that depends only on the multiset of the ids of
 *     its children: leaves get id 0, a node with sorted child ids
 *     c1 <= c2 <= ... gets the trie node reached by walking c1, c2, ... from
 *     the trie root (a hash table stores the trie edges). Equal ids <=> equal
 *     rooted shape, and the trie is shared by both trees of a test case.
 *   - the trees are isomorphic exactly when the two roots get the same id.
 * Nodes are processed in reverse BFS order, so no recursion is needed.
 * Total time O(n log n) (child ids are sorted).
 * Edges that are not valid (self loop, node outside 1..n) or that would make
 * a cycle are ignored, nodes that cannot be reached from the root are not
 * part of the tree.
 *
 * Input : t, then for every test: n, n-1 edges of tree 1, n-1 edges of tree 2.
 * Output: YES / NO for every test.
 *
 * Sample: 2 / 3 / 1 2 / 2 3 / 1 2 / 1 3 / 3 / 1 2 / 2 3 / 1 3 / 3 2 -> NO YES
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define HSIZE (1 << 19)

int head[2][MAXN], nxt[2][2 * MAXN], to[2][2 * MAXN], ecnt[2];
int order[MAXN], par[MAXN], nid[MAXN], vis[MAXN], tmp[MAXN];
int nodesOf[MAXN];                   /* helper for grouping children */

/* hash table: key (trie node, child id) -> next trie node */
long long hkey[HSIZE];
int hval[HSIZE];
int used[MAXN * 2], usedCnt;
int trieCnt;

int compare(const void *a, const void *b)
{
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}

int getChild(int cur, int c)
{
    long long key = ((long long)cur << 32) | (unsigned int)c;
    unsigned int h = (unsigned int)((key * 11400714819323198485ULL) >> 45) & (HSIZE - 1);
    while (hkey[h] != -1)
    {
        if (hkey[h] == key)
            return hval[h];
        h = (h + 1) & (HSIZE - 1);
    }
    hkey[h] = key;
    hval[h] = ++trieCnt;
    used[usedCnt++] = h;
    return hval[h];
}

void addEdge(int g, int u, int v)
{
    to[g][ecnt[g]] = v;
    nxt[g][ecnt[g]] = head[g][u];
    head[g][u] = ecnt[g]++;
}

/* canonical id of the root of tree g */
int canon(int g, int n)
{
    int qh = 0, qt = 0, i, u, v, e, k;
    for (i = 1; i <= n; i++)
    {
        vis[i] = 0;
        nid[i] = 0;
    }
    order[qt++] = 1;
    vis[1] = 1;
    par[1] = 0;
    while (qh < qt)
    {
        u = order[qh++];
        for (e = head[g][u]; e != -1; e = nxt[g][e])
        {
            v = to[g][e];
            if (!vis[v])
            {
                vis[v] = 1;
                par[v] = u;
                order[qt++] = v;
            }
        }
    }
    /* children are handled after their parent in BFS order, so going
       backwards every child id is known before its parent is computed */
    for (i = qt - 1; i >= 0; i--)
    {
        u = order[i];
        k = 0;
        for (e = head[g][u]; e != -1; e = nxt[g][e])
        {
            v = to[g][e];
            if (v != par[u] && par[v] == u)
                tmp[k++] = nid[v];
        }
        qsort(tmp, k, sizeof(int), compare);
        {
            int cur = 0, j;
            for (j = 0; j < k; j++)
                cur = getChild(cur, tmp[j]);
            nid[u] = cur;
        }
    }
    return nid[1];
}

int main()
{
    int t, n, i, a, b, g, id1, id2, j;

    for (j = 0; j < HSIZE; j++)
        hkey[j] = -1;

    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        for (g = 0; g < 2; g++)
        {
            ecnt[g] = 0;
            for (i = 0; i <= n; i++)
                head[g][i] = -1;
            for (i = 0; i < n - 1; i++)
            {
                scanf("%d %d", &a, &b);
                if (a >= 1 && a <= n && b >= 1 && b <= n && a != b)
                {
                    addEdge(g, a, b);
                    addEdge(g, b, a);
                }
            }
        }

        /* clear the hash table entries used by the previous test */
        for (j = 0; j < usedCnt; j++)
            hkey[used[j]] = -1;
        usedCnt = 0;
        trieCnt = 0;

        id1 = canon(0, n);
        id2 = canon(1, n);
        printf(id1 == id2 ? "YES\n" : "NO\n");
    }
    return 0;
}
