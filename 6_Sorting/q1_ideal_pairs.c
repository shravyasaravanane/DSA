/*
 * Sorting - Ideal pairs (Challenge 11)
 * Tina arranges the girls in ascending order of height and the boys in
 * descending order of height. A girl and a boy at the same index form an
 * ideal pair if Ai % Bi == 0 or Bi % Ai == 0.
 * Input : T, then for every test case: n, the heights of the girls and
 *         the heights of the boys.
 * Output: the number of ideal pairs for each test case, one per line.
 *
 * Sample: 4 / 1 6 9 12 / 4 12 3 9 -> 2
 *         4 / 2 2 2 2 / 2 2 2 2   -> 4
 */
#include <stdio.h>
#include <stdlib.h>

int ascending(const void *a, const void *b)
{
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}

int descending(const void *a, const void *b)
{
    int x = *(const int *)a, y = *(const int *)b;
    return (y > x) - (y < x);
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t-- > 0)
    {
        int n;
        scanf("%d", &n);

        int *girls = (int *)malloc(n * sizeof(int));
        int *boys = (int *)malloc(n * sizeof(int));

        for(int i = 0;i<n;i++)
            scanf("%d", &girls[i]);
        for(int i = 0;i<n;i++)
            scanf("%d", &boys[i]);

        qsort(girls, n, sizeof(int), ascending);   /* girls: ascending  */
        qsort(boys, n, sizeof(int), descending);   /* boys: descending  */

        int count = 0;
        for(int i = 0;i<n;i++)
        {
            if (girls[i] % boys[i] == 0 || boys[i] % girls[i] == 0)
                count++;
        }
        printf("%d\n", count);

        free(girls);
        free(boys);
    }
    return 0;
}
