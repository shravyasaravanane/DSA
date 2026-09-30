/*
 * Tree 2 - Flight routes: make the graph strongly connected (Challenge 73)
 * n cities and m one-way flights. Add the minimum number of flights so that
 * it is possible to travel from every city to every other city.
 *
 * Idea:
 *  1. Find the strongly connected components (Tarjan, iterative).
 *  2. In the component graph (a DAG) count the sources (no incoming edge)
 *     and the sinks (no outgoing edge). If there is only one component the
 *     answer is 0, otherwise the answer is max(#sources, #sinks).
 *  3. Construction: run a DFS from every source (visited marks are shared)
 *     and pair it with the first not yet used sink it reaches -> pairs
 *     (s_i, t_i) with s_i ->* t_i.
 *       - cycle edges  t_i -> s_(i+1)  join all pairs into one cycle,
 *       - a sink t' without a pair is joined to a source s' without a pair
 *         by the edge  t' -> s'  (t' is reachable from the cycle and s'
 *         leads back into it),
 *       - what is still left gets  t' -> t_1  (sink)  or  t_1 -> s'  (source).
 *     That is max(#sources, #sinks) edges and the graph becomes strongly
 *     connected. A city (smallest label) represents its component.
 * Time O(n + m).
 *
 * Input : n m, then m lines "a b" (flight a -> b).
 * Output: k, then k lines with the new flights (any valid answer is allowed).
 *
 * Sample: 4 5 / 1 2 / 2 3 / 3 1 / 1 4 / 3 4       -> 1 / 4 1
 *         4 5 / 1 3 / 2 1 / 1 2 / 2 4 / 1 4       -> 2 / 4 3 / 3 1
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 200005

int ea[MAXM], eb[MAXM];
int off[MAXN + 2], adj[MAXM];                 /* CSR graph of the cities */
int idx[MAXN], low[MAXN], onst[MAXN], comp[MAXN], ep[MAXN];
int st[MAXN], cs[MAXN];
int coff[MAXN + 1], cadj[MAXM];               /* CSR graph of the components */
int indeg[MAXN], outdeg[MAXN], rep[MAXN], vis[MAXN];
int srcs[MAXN], snks[MAXN];
int stackNode[MAXN], stackPtr[MAXN];
int ansA[MAXN], ansB[MAXN];

int min(int a, int b)
{
    return a < b ? a : b;
}

int main()
{
    int n, m, i, u, v, s, timer = 0, top = 0, sp = 0, ncomp = 0;
    int p = 0, q = 0, r = 0, k = 0, found, ssp;
    int matchS[MAXN], matchT[MAXN];

    scanf("%d %d", &n, &m);
    i = 0;
    while(m--)
    {
        scanf("%d %d", &ea[i], &eb[i]);
        off[ea[i] + 1]++;
        i++;
    }
    m = i;

    /* CSR in input order: the edges of u are adj[off[u] .. off[u+1]-1] */
    for (i = 1; i <= n + 1; i++)
        off[i] += off[i - 1];
    {
        int *pos = (int *)malloc((n + 2) * sizeof(int));
        for (i = 0; i <= n + 1; i++)
            pos[i] = off[i];
        for (i = 0; i < m; i++)
            adj[pos[ea[i]]++] = eb[i];
        free(pos);
    }

    /* iterative Tarjan */
    for (s = 1; s <= n; s++)
    {
        if (idx[s])
            continue;
        cs[sp++] = s;
        idx[s] = low[s] = ++timer;
        st[top++] = s;
        onst[s] = 1;
        ep[s] = off[s];
        while (sp > 0)
        {
            u = cs[sp - 1];
            if (ep[u] < off[u + 1])
            {
                v = adj[ep[u]++];
                if (!idx[v])
                {
                    idx[v] = low[v] = ++timer;
                    st[top++] = v;
                    onst[v] = 1;
                    ep[v] = off[v];
                    cs[sp++] = v;
                }
                else if (onst[v])
                    low[u] = min(low[u], idx[v]);
            }
            else
            {
                if (low[u] == idx[u])
                {
                    do
                    {
                        v = st[--top];
                        onst[v] = 0;
                        comp[v] = ncomp;
                    } while (v != u);
                    ncomp++;
                }
                sp--;
                if (sp > 0)
                    low[cs[sp - 1]] = min(low[cs[sp - 1]], low[u]);
            }
        }
    }

    if (ncomp == 1)
    {
        printf("0\n");
        return 0;
    }

    /* smallest city of every component is its representative */
    for (i = 0; i < ncomp; i++)
        rep[i] = 0;
    for (i = n; i >= 1; i--)
        rep[comp[i]] = i;

    /* component graph (CSR in input order) */
    for (i = 0; i < m; i++)
    {
        int a = comp[ea[i]], b = comp[eb[i]];
        if (a != b)
        {
            coff[a + 1]++;
            outdeg[a]++;
            indeg[b]++;
        }
    }
    for (i = 1; i <= ncomp; i++)
        coff[i] += coff[i - 1];
    {
        int *pos = (int *)malloc((ncomp + 1) * sizeof(int));
        for (i = 0; i < ncomp; i++)
            pos[i] = coff[i];
        for (i = 0; i < m; i++)
        {
            int a = comp[ea[i]], b = comp[eb[i]];
            if (a != b)
                cadj[pos[a]++] = b;
        }
        free(pos);
    }

    for (i = 0; i < ncomp; i++)
    {
        if (indeg[i] == 0)
            srcs[p++] = i;
        if (outdeg[i] == 0)
            snks[q++] = i;
    }

    /* pair every source with a sink it reaches (shared visited marks) */
    for (i = 0; i < p; i++)
    {
        s = srcs[i];
        if (vis[s])
            continue;
        found = -1;
        ssp = 0;
        vis[s] = 1;
        stackNode[ssp] = s;
        stackPtr[ssp++] = coff[s];
        if (outdeg[s] == 0)
            found = s;
        while (ssp > 0 && found == -1)
        {
            u = stackNode[ssp - 1];
            if (stackPtr[ssp - 1] < coff[u + 1])
            {
                v = cadj[stackPtr[ssp - 1]++];
                if (!vis[v])
                {
                    vis[v] = 1;
                    if (outdeg[v] == 0)
                        found = v;
                    else
                    {
                        stackNode[ssp] = v;
                        stackPtr[ssp++] = coff[v];
                    }
                }
            }
            else
                ssp--;
        }
        if (found != -1)
        {
            matchS[r] = s;
            matchT[r] = found;
            r++;
            vis[s] = 1;
        }
    }

    /* sources / sinks without a pair: a leftover sink is reachable from the
       cycle and a leftover source reaches the cycle, so a leftover sink can
       be joined directly to a leftover source; the ones that stay over are
       tied to the cycle through the first matched sink */
    {
        int *usedS = (int *)calloc(ncomp, sizeof(int));
        int *usedT = (int *)calloc(ncomp, sizeof(int));
        int nls = 0, nlt = 0, j;
        int *ls = (int *)malloc(ncomp * sizeof(int));
        int *lt = (int *)malloc(ncomp * sizeof(int));
        for (i = 0; i < r; i++)
        {
            usedS[matchS[i]] = 1;
            usedT[matchT[i]] = 1;
        }
        for (i = 0; i < p; i++)
            if (!usedS[srcs[i]])
                ls[nls++] = srcs[i];
        for (i = 0; i < q; i++)
            if (!usedT[snks[i]])
                lt[nlt++] = snks[i];
        for (j = 0; j < nls && j < nlt; j++)
        {
            ansA[k] = rep[lt[j]];
            ansB[k++] = rep[ls[j]];
        }
        for (; j < nlt; j++)
        {
            ansA[k] = rep[lt[j]];
            ansB[k++] = rep[matchT[0]];
        }
        for (; j < nls; j++)
        {
            ansA[k] = rep[matchT[0]];
            ansB[k++] = rep[ls[j]];
        }
        free(usedS);
        free(usedT);
        free(ls);
        free(lt);
    }
    for (i = 0; i < r; i++)
    {
        ansA[k] = rep[matchT[i]];
        ansB[k++] = rep[matchS[(i + 1) % r]];
    }

    printf("%d\n", k);
    for (i = 0; i < k; i++)
        printf("%d %d\n", ansA[i], ansB[i]);
    return 0;
}
