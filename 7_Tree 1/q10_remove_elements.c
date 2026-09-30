/*
 * Tree 1 - Removing elements from the list (Challenge 70)
 * List of n integers. For every position p_i remove the element that is
 * currently at that position (positions are counted in the CURRENT list)
 * and report the removed element.
 *
 * Idea: segment tree that stores how many elements are still present in
 * each range. To remove the p-th present element we walk down from the root:
 * go left if the left child holds at least p elements, otherwise subtract
 * the left count from p and go right. Every removal decrements the counts on
 * the way down. build: O(n), each removal: O(log n).
 *
 * Input : n, the n elements, then the n positions.
 * Output: the elements in the order they are removed.
 *
 * Sample: 5 / 2 6 1 4 2 / 3 1 3 1 1 -> 1 2 2 6 4
 */
#include <stdio.h>
#include <stdlib.h>

int *tree;

void build(int k,int l,int r)
{
    int mid;
    tree[k] = r - l + 1;                 /* every element is present */
    if (l == r)
        return;
    mid = (l + r) / 2;
    build(2 * k, l, mid);
    build(2 * k + 1, mid + 1, r);
}

/* removes the p-th present element of [l, r] and returns its index */
int removeKth(int k, int l, int r, int p)
{
    int mid;
    tree[k]--;
    if (l == r)
        return l;
    mid = (l + r) / 2;
    if (tree[2 * k] >= p)
        return removeKth(2 * k, l, mid, p);
    return removeKth(2 * k + 1, mid + 1, r, p - tree[2 * k]);
}

int main()
{
    int n, i, p, idx;
    int *x;

    scanf("%d", &n);
    x = (int *)malloc((n + 1) * sizeof(int));
    tree = (int *)malloc(4 * (n + 1) * sizeof(int));
    for (i = 1; i <= n; i++)
        scanf("%d", &x[i]);

    build(1, 1, n);

    for (i = 0; i < n; i++)
    {
        scanf("%d", &p);
        idx = removeKth(1, 1, n, p);
        if (i > 0)
            printf(" ");
        printf("%d", x[idx]);
    }
    printf("\n");
    return 0;
}
