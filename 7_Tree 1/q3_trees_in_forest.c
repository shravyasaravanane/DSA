/*
 * Tree 1 - Forest queries (Challenge 63)
 * n x n map, '.' is empty and '*' is a tree. For every query
 * "y1 x1 y2 x2" print the number of trees inside that rectangle.
 *
 * Idea: 2D prefix sums.  sum[i][j] = trees in the rectangle (1,1)-(i,j)
 *   sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + tree(i,j)
 * and every query is answered in O(1):
 *   sum[y2][x2] - sum[y1-1][x2] - sum[y2][x1-1] + sum[y1-1][x1-1]
 *
 * Input : n q, n lines of the map, q lines "y1 x1 y2 x2".
 * Output: one number per query.
 *
 * Sample: 4 3 / .*.. / *.** / **.. / **** / 2 2 3 4 / 3 1 3 1 / 1 1 2 2
 *         -> 3 1 2
 */
#include <stdio.h>

int sum[1005][1005];
char row[1005];

int main()
{
    int n, q, i, j, y1, x1, y2, x2;

    scanf("%d %d", &n, &q);
    for(i=1;i<=n;i++)
    {
        scanf("%s", row);
        for (j = 1; j <= n; j++)
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1]
                        + (row[j - 1] == '*' ? 1 : 0);
    }

    while (q-- > 0)
    {
        scanf("%d %d %d %d", &y1, &x1, &y2, &x2);
        printf("%d\n", sum[y2][x2] - sum[y1 - 1][x2] - sum[y2][x1 - 1] + sum[y1 - 1][x1 - 1]);
    }
    return 0;
}
