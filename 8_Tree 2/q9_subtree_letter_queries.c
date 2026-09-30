/*
 * Tree 2 - Letters in a subtree (Challenge 79)
 * Rooted tree (root 1), every node holds a lowercase letter. For every query
 * "u c" print how many nodes of the subtree of u hold the letter c.
 *
 * Idea: a DFS (iterative, so no deep recursion) gives every node an entry
 * time tin[u] and an exit time tout[u]; the subtree of u is exactly the
 * block tin[u]..tout[u] of the visiting order. For every letter a prefix
 * count over the visiting order is stored, so a query is
 *      pre[c][tout[u]] - pre[c][tin[u] - 1]      in O(1).
 * Nodes that cannot be reached from the root (invalid input) count as 0.
 *
 * Input : N Q, the string s (letter of node i = s[i]), N-1 edges, then Q
 *         lines "u c".
 * Output: one number per query.
 *
 * Sample: 3 1 / aba / 1 2 / 1 3 / 1 a -> 2
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005

int head[MAXN], nxt[2 * MAXN], to[2 * MAXN], ecnt;
int tin[MAXN], tout[MAXN], ptr[MAXN], par[MAXN], stk[MAXN], order[MAXN];
int pre[26][MAXN];
char s[MAXN + 5];

void addEdge(int u, int v)
{
    to[ecnt] = v;
    nxt[ecnt] = head[u];
    head[u] = ecnt++;
}

int main()
{
    int N, Q, i, u, v, c, timer = 0, sp = 0, len;
    char ch;

    scanf("%d %d", &N, &Q);
    scanf("%s", s);
    len = strlen(s);

    for (i = 1; i <= N; i++)
        head[i] = -1;
    for(i = 0;i<N-1;i ++)
    {
        scanf("%d %d", &u, &v);
        if (u >= 1 && u <= N && v >= 1 && v <= N && u != v)
        {
            addEdge(u, v);
            addEdge(v, u);
        }
    }

    /* iterative DFS from the root */
    stk[sp++] = 1;
    tin[1] = ++timer;
    order[timer] = 1;
    par[1] = 0;
    ptr[1] = head[1];
    while (sp > 0)
    {
        u = stk[sp - 1];
        if (ptr[u] != -1)
        {
            v = to[ptr[u]];
            ptr[u] = nxt[ptr[u]];
            if (v != par[u] && tin[v] == 0)
            {
                par[v] = u;
                tin[v] = ++timer;
                order[timer] = v;
                ptr[v] = head[v];
                stk[sp++] = v;
            }
        }
        else
        {
            tout[u] = timer;
            sp--;
        }
    }

    for (i = 1; i <= timer; i++)
    {
        for (c = 0; c < 26; c++)
            pre[c][i] = pre[c][i - 1];
        u = order[i];
        if (u - 1 < len && s[u - 1] >= 'a' && s[u - 1] <= 'z')
            pre[s[u - 1] - 'a'][i]++;
    }

    while(Q--)
    {
        scanf("%d %c", &u, &ch);
        if (u < 1 || u > N || tin[u] == 0 || ch < 'a' || ch > 'z')
            printf("0\n");
        else
            printf("%d\n", pre[ch - 'a'][tout[u]] - pre[ch - 'a'][tin[u] - 1]);
    }
    return 0;
}
