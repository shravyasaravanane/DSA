/*
 * Tree 1 - Tree traversals: postorder from preorder + inorder (Challenge 62)
 * The nodes are labelled 1..n. Preorder = root, left, right and
 * inorder = left, root, right, so the first preorder element is the root and
 * its position in the inorder list splits the left and right subtrees.
 * Recursing on both halves and printing the root last gives the postorder.
 *
 * Idea: pos[v] = index of v in the inorder list (O(1) lookup), so the whole
 * reconstruction is O(n).
 *
 * Input : n, the preorder line, the inorder line.
 * Output: the postorder line.
 *
 * Sample: 5 / 5 3 2 1 4 / 3 5 1 2 4 -> 3 1 4 2 5
 */
#include <stdio.h>
#include <stdlib.h>

int *pre, *in, *pos, *post;
int preIdx = 0, cnt = 0;

/* builds the subtree whose inorder range is [lo, hi] */
void build(int lo, int hi)
{
    int root, mid;
    if (lo > hi)
        return;
    root = pre[preIdx++];
    mid = pos[root];
    build(lo, mid - 1);
    build(mid + 1, hi);
    post[cnt++] = root;
}

int main()
{
    int n, i;

    scanf("%d", &n);
    pre  = (int *)malloc((n + 1) * sizeof(int));
    in   = (int *)malloc((n + 1) * sizeof(int));
    pos  = (int *)malloc((n + 1) * sizeof(int));
    post = (int *)malloc((n + 1) * sizeof(int));

    for(i=1;i<=n;i++)
        scanf("%d", &pre[i - 1]);
    for(i=1;i<=n;i++)
    {
        scanf("%d", &in[i - 1]);
        pos[in[i - 1]] = i - 1;
    }

    build(0, n - 1);

    for (i = 0; i < cnt; i++)
    {
        if (i > 0)
            printf(" ");
        printf("%d", post[i]);
    }
    printf("\n");
    return 0;
}
