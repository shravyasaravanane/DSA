/*
 * Tree 2 - Prufer code: rebuild the tree (Challenge 75)
 * The code of a tree with n nodes has n-2 numbers: repeatedly take the leaf
 * with the smallest label, write down its only neighbour and remove the leaf.
 * Given the code, print the edges of the tree.
 *
 * Idea (linear time): deg[v] = 1 + number of times v is in the code. The
 * smallest current leaf is tracked with a pointer 'ptr'. For every code
 * element v the edge (leaf, v) is printed and deg[v] is decreased; if v
 * itself became a leaf smaller than ptr it is the next leaf, otherwise ptr
 * moves on to the next leaf. At the end the last leaf and node n remain.
 * (The usual C++ solution keeps the leaves in a priority queue and calls
 *  q.pop(); the pointer trick gives the same leaf order without a heap.)
 *
 * Input : n, then the n-2 numbers of the code.
 * Output: the n-1 edges, in the order in which the leaves are removed.
 *
 * Sample: 5 / 2 2 4 -> 1 2 / 3 2 / 2 4 / 4 5
 *         5 / 3 1 2 -> 4 3 / 3 1 / 1 2 / 2 5
 */
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, i, v, ptr, leaf;
    int *code, *deg;

    scanf("%d", &n);
    code = (int *)malloc((n + 1) * sizeof(int));
    deg  = (int *)malloc((n + 2) * sizeof(int));

    for (i = 1; i <= n; i++)
        deg[i] = 1;
    for (i = 0; i < n - 2; i++)
    {
        scanf("%d", &code[i]);
        deg[code[i]]++;
    }

    ptr = 1;
    while (deg[ptr] != 1)
        ptr++;
    leaf = ptr;

    for (i = 0; i < n - 2; i++)
    {
        v = code[i];
        printf("%d %d\n", leaf, v);
        deg[v]--;
        if (deg[v] == 1 && v < ptr)
            leaf = v;
        else
        {
            ptr++;
            while (deg[ptr] != 1)
                ptr++;
            leaf = ptr;
        }
    }
    printf("%d %d\n", leaf, n);
    return 0;
}
