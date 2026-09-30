/*
 * Sorting - Minimum scalar product (Challenge 17)
 * Given two arrays A and B of size n, find the minimum value of
 * A[0]*B[0] + A[1]*B[1] + ... + A[n-1]*B[n-1] when the elements of both
 * arrays may be shuffled.
 * Idea: sort A in ascending order and B in descending order, then
 * multiply element by element.
 *
 * Input : T, then for every test case: N, array A, array B.
 * Output: the minimum value for every test case on a new line.
 *
 * Sample: 4 / 2 5 3 7 / 8 5 7 3                   -> 83
 *         3 / 13 11 1 / 6 15 14                   -> 247
 *         5 / 6 11 9 15 4 / 3 41 8 21 4           -> 451
 */
#include <stdio.h>

/* flag = 1 : ascending order, flag = 0 : descending order */
void sort(int a[],int n,int flag)
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if ((flag == 1 && a[j] > a[j + 1]) ||
                (flag == 0 && a[j] < a[j + 1]))
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int t, n, i;
    int a[50], b[50];
    long sum;

    scanf("%d", &t);
    while (t-- > 0)
    {
        scanf("%d", &n);
        for (i = 0; i < n; i++)
            scanf("%d", &a[i]);
        for (i = 0; i < n; i++)
            scanf("%d", &b[i]);

        sort(a, n, 1);   /* A ascending  */
        sort(b, n, 0);   /* B descending */

        sum = 0;
        for (i = 0; i < n; i++)
            sum += (long)a[i] * b[i];

        printf("%ld\n", sum);
    }
    return 0;
}
