/*
 * Sorting - Organizing containers of fruits (Challenge 13)
 * containers[i][j] = number of fruits of type j in container i (n x n).
 * A swap moves a fruit between two containers. It is possible to make
 * every container hold only one type (and each type in one container)
 * exactly when the sorted list of container totals (row sums) equals the
 * sorted list of type totals (column sums).
 *
 * Input : q, then for every query: n and the n x n matrix.
 * Output: "Possible" or "Impossible" for every query.
 *
 * Sample: 2 / 1 1 / 1 1     -> Possible
 *         2 / 0 2 / 1 1     -> Impossible
 */
#include <stdio.h>

void insertionSort(long int *p,long int n)
{
    long int i, j, key;
    for (i = 1; i < n; i++)
    {
        key = p[i];
        j = i - 1;
        while (j >= 0 && p[j] > key)
        {
            p[j + 1] = p[j];
            j--;
        }
        p[j + 1] = key;
    }
}

int main()
{
    int q, n, i, j, possible;
    long int value;
    long int rows[100], cols[100];

    scanf("%d", &q);
    while(q--)
    {
        scanf("%d", &n);

        for(i=0;i<n;i++)
        {
            rows[i] = 0;
            cols[i] = 0;
        }

        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                scanf("%ld", &value);
                rows[i] += value;   /* balls in container i */
                cols[j] += value;   /* balls of type j      */
            }
        }

        insertionSort(rows, n);
        insertionSort(cols, n);

        possible = 1;
        for(i=0;i<n;i++)
        {
            if (rows[i] != cols[i])
            {
                possible = 0;
                break;
            }
        }
        printf(possible ? "Possible\n" : "Impossible\n");
    }
    return 0;
}
