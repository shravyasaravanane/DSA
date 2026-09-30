/*
 * Searching - Circuit board (Challenge 3)
 * R x C board of thinness values. A sub-rectangle is beautiful if in EACH
 * of its rows the difference between the largest and the smallest value is
 * at most L. Find the largest beautiful sub-rectangle (number of squares).
 *
 * Idea: fix the left column c1 and grow the right column c2, keeping the
 * min and max of every row for the segment [c1..c2].  ok[c1][c2][r] tells
 * whether row r is fine for these columns. For every (c1,c2) the longest
 * run of consecutive fine rows gives the best height, area = height*width.
 * Complexity O(C * C * R).
 *
 * Input : T, then for every case: R C L and the R x C matrix.
 * Output: the maximum number of squares for every case.
 *
 * Sample: 1 4 0 / 3 1 3 3 ; 2 3 0 / 4 4 5 / 7 6 6 ; ... -> 2 2 6
 */
#include <stdio.h>
#include <stdbool.h>

int A[309][309];
bool ok[309][309][309];

int main()
{
    int t, r, c, l, i, c1, c2, run, best;
    int mn[309], mx[309];

    scanf("%d", &t);
    while (t-- > 0)
    {
        scanf("%d %d %d", &r, &c, &l);
        for (i = 0; i < r; i++)
            for (c1 = 0; c1 < c; c1++)
                scanf("%d", &A[i][c1]);

        best = 0;
        for (c1 = 0; c1 < c; c1++)
        {
            for (i = 0; i < r; i++)
            {
                mn[i] = A[i][c1];
                mx[i] = A[i][c1];
            }
            for (c2 = c1; c2 < c; c2++)
            {
                run = 0;
                for (i = 0; i < r; i++)
                {
                    if (A[i][c2] < mn[i])
                        mn[i] = A[i][c2];
                    if (A[i][c2] > mx[i])
                        mx[i] = A[i][c2];

                    ok[c1][c2][i] = (mx[i] - mn[i] <= l);

                    if (ok[c1][c2][i])
                    {
                        run++;
                        if (run * (c2 - c1 + 1) > best)
                            best = run * (c2 - c1 + 1);
                    }
                    else
                        run = 0;
                }
            }
        }
        printf("%d\n", best);
    }
    return 0;
}
