/*
 * Tree 1 - Different trips in Byteland (Challenge 67)
 * A trip goes from a city A up to a city B that lies on the shortest path
 * from A to the capital (city 1); A = B is allowed. Two cities are "similar"
 * when they have the same number of roads (same degree), and two trips are
 * similar when they have the same length and their i-th cities are similar.
 * We need the number of pairwise different trips.
 *
 * Idea: replace every city by its degree. A trip is then a string of
 * degrees read upwards; reading it downwards from B to A gives the reverse
 * string, so the answer is the number of DIFFERENT strings that can be read
 * on downward paths of the tree rooted at city 1 (a substring count on a
 * tree).  Build a suffix automaton over the tree:
 *   - visit the cities in BFS order and extend the automaton from the state
 *     of the parent with the degree of the city (generalised suffix
 *     automaton, an already existing transition is reused / cloned),
 *   - the number of different strings is the sum of len[v] - len[link[v]]
 *     over all states.
 * Complexity is about O(N * distinct degrees), and there are at most
 * about sqrt(2N) different degrees.
 *
 * Input : N, then N-1 lines "u v".
 * Output: the maximum number of different trips.
 *
 * Sample: 3 / 2 1 / 3 1                 -> 3
 *         4 / 2 1 / 3 1 / 2 4           -> 5
 *
 * Note: the tree is limited to N <= 100000 (2N+1 states must fit in st[]).
 * The original C++ text used  const int MAXL=200005;  which is not allowed
 * as an array size in C, so a #define with the same value is used below.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXL 200005          /* const int MAXL=200005; in the C++ version */

typedef struct state
{
    int len, link, head;     /* head = first transition of the state */
} state;

state st[MAXL];
int sz = 1;                  /* state 0 is the initial state */

/* transitions stored as linked lists: edge e goes to eto[e] with label elab[e] */
int *eto, *elab, *enext;
int ecnt = 0, ecap = 0;

int findNext(int s, int c)
{
    int e;
    for (e = st[s].head; e != -1; e = enext[e])
        if (elab[e] == c)
            return e;
    return -1;
}

void addEdge(int s, int c, int to)
{
    if (ecnt == ecap)
    {
        ecap = ecap ? ecap * 2 : 1 << 20;
        eto   = (int *)realloc(eto,   ecap * sizeof(int));
        elab  = (int *)realloc(elab,  ecap * sizeof(int));
        enext = (int *)realloc(enext, ecap * sizeof(int));
    }
    eto[ecnt] = to;
    elab[ecnt] = c;
    enext[ecnt] = st[s].head;
    st[s].head = ecnt++;
}

/* makes a copy of state q with the given length and returns it */
int cloneState(int q, int len)
{
    int e, cl = sz++;
    st[cl].len = len;
    st[cl].link = st[q].link;
    st[cl].head = -1;
    for (e = st[q].head; e != -1; e = enext[e])
        addEdge(cl, elab[e], eto[e]);
    return cl;
}

/* extends the automaton from state 'last' with character c, returns new state */
int extend(int last, int c)
{
    int p, q, cur, cl, e;

    e = findNext(last, c);
    if (e != -1)                         /* transition already exists */
    {
        q = eto[e];
        if (st[q].len == st[last].len + 1)
            return q;
        cl = cloneState(q, st[last].len + 1);
        st[q].link = cl;
        for (p = last; p != -1; p = st[p].link)
        {
            e = findNext(p, c);
            if (e == -1 || eto[e] != q)
                break;
            eto[e] = cl;
        }
        return cl;
    }

    cur = sz++;
    st[cur].len = st[last].len + 1;
    st[cur].head = -1;
    for (p = last; p != -1; p = st[p].link)
    {
        if (findNext(p, c) != -1)
            break;
        addEdge(p, c, cur);
    }
    if (p == -1)
        st[cur].link = 0;
    else
    {
        q = eto[findNext(p, c)];
        if (st[p].len + 1 == st[q].len)
            st[cur].link = q;
        else
        {
            cl = cloneState(q, st[p].len + 1);
            for (; p != -1; p = st[p].link)
            {
                e = findNext(p, c);
                if (e == -1 || eto[e] != q)
                    break;
                eto[e] = cl;
            }
            st[q].link = cl;
            st[cur].link = cl;
        }
    }
    return cur;
}

int main()
{
    int n, i, u, v, e, head, tail;
    int *deg, *ahead, *anext, *ato, *queue, *par, *sstate;
    long long ans = 0;

    scanf("%d", &n);
    deg    = (int *)calloc(n + 1, sizeof(int));
    ahead  = (int *)malloc((n + 1) * sizeof(int));
    anext  = (int *)malloc(2 * n * sizeof(int));
    ato    = (int *)malloc(2 * n * sizeof(int));
    queue  = (int *)malloc((n + 1) * sizeof(int));
    par    = (int *)calloc(n + 1, sizeof(int));
    sstate = (int *)malloc((n + 1) * sizeof(int));

    for (i = 0; i <= n; i++)
        ahead[i] = -1;
    e = 0;
    for (i = 0; i < n - 1; i++)
    {
        scanf("%d %d", &u, &v);
        ato[e] = v; anext[e] = ahead[u]; ahead[u] = e++;
        ato[e] = u; anext[e] = ahead[v]; ahead[v] = e++;
        deg[u]++;
        deg[v]++;
    }

    st[0].len = 0;
    st[0].link = -1;
    st[0].head = -1;

    /* BFS from the capital; sstate[c] = automaton state of the path root..c */
    head = tail = 0;
    queue[tail++] = 1;
    par[1] = -1;
    sstate[1] = extend(0, deg[1]);
    while (head < tail)
    {
        u = queue[head++];
        for (e = ahead[u]; e != -1; e = anext[e])
        {
            v = ato[e];
            if (v == par[u])
                continue;
            par[v] = u;
            sstate[v] = extend(sstate[u], deg[v]);
            queue[tail++] = v;
        }
    }

    for (i = 1; i < sz; i++)
        ans += st[i].len - st[st[i].link].len;

    printf("%lld\n", ans);
    return 0;
}
