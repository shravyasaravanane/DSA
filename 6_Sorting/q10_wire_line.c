/*
 * Sorting - Wire line across the village (Challenge 20)
 * There are n flats at (xi, yi) with hi persons in each. The wire line is
 * parallel to y = x, so it has the form y = x + c. A flat is on the left
 * of the line when (yi - xi) > c and on the right when (yi - xi) < c.
 * The line is effective only if the persons on the left and on the right
 * are equal (persons living exactly on the line are on neither side).
 *
 * Idea: d = yi - xi decides the side of every flat. Sort the flats by d,
 * merge flats with equal d into groups and build prefix sums P[k] of the
 * persons in the first k groups (S = total persons).
 *   - line between group k and group k+1 : P[k] == S - P[k]
 *   - line passing through group k       : P[k-1] == S - P[k]
 * P is strictly increasing, so both checks are done with binary search.
 *
 * Input : t, then for every test case: n and n lines "xi yi hi".
 * Output: "YES" or "NO" for every test case.
 *
 * Sample: 3 / 3 / -2 1 1 / -1 1 3 / 1 -1 4 / 3 / ... -> YES NO NO
 */
#include <stdio.h>

struct flat
{
    int d;      /* yi - xi        */
    long h;     /* persons living */
};

/* value that must equal 'target' at index k of the prefix sums */
long value(long P[], int k, int mode)
{
    if (mode == 0)
        return P[k];                 /* line between two groups   */
    return P[k - 1] + P[k];          /* line passing through group */
}

/* binary search for target in the increasing values k = lo..hi */
int search(long P[], int lo, int hi, long target, int mode)
{
    int l = lo, r = hi;
    while(l<= r)
    {
        int mid = (l+r)/2;
        long v = value(P, mid, mode);
        if (v == target)
            return 1;
        if (v < target)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return 0;
}

int main()
{
    int t, n, x, y, j;
    long h;
    struct flat f[2005], key;
    long P[2005];

    scanf("%d", &t);
    while(t-->0)
    {
        scanf("%d", &n);
        for(int i = 0;i < n;i++)
        {
            scanf("%d %d %ld", &x, &y, &h);
            f[i].d = y - x;
            f[i].h = h;
        }

        /* insertion sort of the flats by d */
        for (int i = 1; i < n; i++)
        {
            key = f[i];
            j = i - 1;
            while (j >= 0 && f[j].d > key.d)
            {
                f[j + 1] = f[j];
                j--;
            }
            f[j + 1] = key;
        }

        /* merge equal d values into groups, P[k] = persons in first k groups */
        int m = 0;
        P[0] = 0;
        for(int i = 0;i < n;i++)
        {
            if (i == 0 || f[i].d != f[i - 1].d)
            {
                m++;
                P[m] = P[m - 1];
            }
            P[m] += f[i].h;
        }
        long S = P[m];

        int possible = 0;
        if (S % 2 == 0 && m >= 2)
            possible = search(P, 1, m - 1, S / 2, 0);
        if (!possible)
            possible = search(P, 1, m, S, 1);

        printf(possible ? "YES\n" : "NO\n");
    }
    return 0;
}
