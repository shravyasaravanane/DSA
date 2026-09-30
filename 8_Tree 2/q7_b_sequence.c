/*
 * Tree 2 - B-sequence insertions (Challenge 77)
 * A B-sequence is strictly increasing up to its maximum and then strictly
 * decreasing; the maximum appears once, every other value at most twice
 * (once in each part) and every value of the decreasing part also appears
 * in the increasing part.
 * For every value val: insert it only if the sequence stays a B-sequence,
 * and print the size after each operation; at the end print the sequence.
 *
 * Idea: the sequence is fully described by how many times each value occurs
 * (1 = only in the increasing part, 2 = in both parts) and by its maximum.
 * For a value val and the current maximum mx:
 *      val > mx            : val becomes the new maximum (count 1)   accept
 *      val == mx           : the maximum would appear twice           reject
 *      val < mx, count 0   : goes into the increasing part            accept
 *      val < mx, count 1   : goes into the decreasing part            accept
 *      val < mx, count 2   : already in both parts                    reject
 * All values (sequence + operations) are sorted and compressed once, so the
 * counts are kept in an array and every operation costs O(log n) (binary
 * search). The final sequence is the values with count >= 1 in ascending
 * order followed by the values with count 2 in descending order.
 *
 * Input : N, the sequence, Q, then Q values.
 * Output: the size after every operation, then the final sequence.
 *
 * Sample: 4 / 1 2 5 2 / 4 / 5 1 3 2 -> 4 5 6 6 / 1 2 3 5 2 1
 */
#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}

int position(int *v, int m, int x)
{
    int lo = 0, hi = m - 1, mid;
    while (lo <= hi)
    {
        mid = (lo + hi) / 2;
        if (v[mid] == x)
            return mid;
        if (v[mid] < x)
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    return -1;
}

int main()
{
    int N, Q, i, m, total, size, mx = 0, id, first = 1;
    int *s, *ops, *vals, *cnt;

    scanf("%d", &N);
    s = (int *)malloc(N * sizeof(int));
    for(i=0;i<N;i++)
        scanf("%d", &s[i]);
    scanf("%d", &Q);
    ops = (int *)malloc((Q + 1) * sizeof(int));
    for (i = 0; i < Q; i++)
        scanf("%d", &ops[i]);

    vals = (int *)malloc((N + Q + 1) * sizeof(int));
    total = 0;
    for (i = 0; i < N; i++)
        vals[total++] = s[i];
    for (i = 0; i < Q; i++)
        vals[total++] = ops[i];
    qsort(vals, total, sizeof(int), compare);
    m = 0;
    for (i = 0; i < total; i++)
        if (i == 0 || vals[i] != vals[i - 1])
            vals[m++] = vals[i];

    cnt = (int *)calloc(m + 1, sizeof(int));
    for (i = 0; i < N; i++)
    {
        cnt[position(vals, m, s[i])]++;
        if (s[i] > mx)
            mx = s[i];
    }
    size = N;

    for (i = 0; i < Q; i++)
    {
        id = position(vals, m, ops[i]);
        if (ops[i] > mx)
        {
            cnt[id] = 1;
            mx = ops[i];
            size++;
        }
        else if (ops[i] < mx && cnt[id] < 2)
        {
            cnt[id]++;
            size++;
        }
        printf("%d\n", size);
    }

    for (i = 0; i < m; i++)
        if (cnt[i] >= 1)
        {
            if (!first)
                printf(" ");
            printf("%d", vals[i]);
            first = 0;
        }
    for (i = m - 1; i >= 0; i--)
        if (cnt[i] == 2)
        {
            if (!first)
                printf(" ");
            printf("%d", vals[i]);
            first = 0;
        }
    printf("\n");
    return 0;
}
