/*
 * Graph - Udaya family pizza (Challenge 82)  ->  2-SAT
 * Every family member gives two wishes "+ x" (topping x is included) or
 * "- x" (topping x is not included); at least one of the two must hold.
 *
 * Each topping x gets two graph nodes: 2x+1 (topping IN, wish "+ x") and
 * 2x (topping OUT, wish "- x"); the opposite literal of node a is a^1.
 * A member with wishes (a OR b) gives the implications
 *        not a -> b     and     not b -> a
 * The wishes can be met iff no topping lies in the same strongly connected
 * component as its opposite. Components are found with an iterative Tarjan
 * (no deep recursion). Tarjan numbers components in reverse topological
 * order, so the topping is included when comp[2x+1] < comp[2x].
 *
 * Input : n m, then n lines "s x s x" with s = '+' or '-'.
 * Output: m symbols (space separated) or IMPOSSIBLE.
 *
 * Sample: 3 5 / + 1 + 2 / - 1 + 3 / + 4 - 2  ->  - + + + -
 */
#include <stdio.h>

#define MAXV 200010
#define MAXE 200010

int head[MAXV], nxt[MAXE], to[MAXE], ec = 0;
int num[MAXV], low[MAXV], comp[MAXV], onst[MAXV], cur[MAXV];
int stk[MAXV], cs[MAXV];
int timer = 0, ncomp = 0;

/* add the implication i -> j */
void link(int i,int j)
{
    ec++;
    to[ec] = j;
    nxt[ec] = head[i];
    head[i] = ec;
}

/* iterative Tarjan starting from node 'start' */
void scc(int start)
{
    int top = 0, sp = 0, u, v, e, p;
    num[start] = low[start] = ++timer;
    stk[sp++] = start;
    onst[start] = 1;
    cur[start] = head[start];
    cs[top++] = start;

    while (top > 0)
    {
        u = cs[top - 1];
        if (cur[u])
        {
            e = cur[u];
            cur[u] = nxt[e];
            v = to[e];
            if (!num[v])
            {
                num[v] = low[v] = ++timer;
                stk[sp++] = v;
                onst[v] = 1;
                cur[v] = head[v];
                cs[top++] = v;
            }
            else if (onst[v] && num[v] < low[u])
                low[u] = num[v];
        }
        else
        {
            if (low[u] == num[u])
            {
                do
                {
                    v = stk[--sp];
                    onst[v] = 0;
                    comp[v] = ncomp;
                } while (v != u);
                ncomp++;
            }
            top--;
            if (top > 0)
            {
                p = cs[top - 1];
                if (low[u] < low[p])
                    low[p] = low[u];
            }
        }
    }
}

int main()
{
    int n, m, i, x, y, a, b;
    char s1, s2;

    scanf("%d %d", &n, &m);
    for (i = 0; i < n; i++)
    {
        scanf(" %c %d %c %d", &s1, &x, &s2, &y);
        a = 2 * (x - 1) + (s1 == '+' ? 1 : 0);
        b = 2 * (y - 1) + (s2 == '+' ? 1 : 0);
        link(a ^ 1, b);
        link(b ^ 1, a);
    }

    for (i = 0; i < 2 * m; i++)
        if (!num[i])
            scc(i);

    for (i = 0; i < m; i++)
    {
        if (comp[2 * i] == comp[2 * i + 1])
        {
            printf("IMPOSSIBLE\n");
            return 0;
        }
    }
    for (i = 0; i < m; i++)
    {
        if (i > 0)
            printf(" ");
        printf("%c", comp[2 * i + 1] < comp[2 * i] ? '+' : '-');
    }
    printf("\n");
    return 0;
}
