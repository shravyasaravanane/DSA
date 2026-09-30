/*
 * Hashing - Pikachus who hate evolution (Challenge 91)
 * Count the distinct pairs (Ai, Aj) with i < j (a pair is a tuple of values,
 * so (1,2) and (2,1) are different, equal tuples are counted once).
 * Sample 1: 1 2 2 1 3 -> (1,2)(1,1)(1,3)(2,2)(2,1)(2,3) = 6.
 *
 * The tuple (x, y) exists iff first[x] < last[y]  (for x == y: the value
 * occurs at least twice, which is again first[x] < last[x]). So
 *      answer = sum over distinct y of #{distinct x : first[x] < last[y]}
 * A hash table (open addressing) maps every value to an id, remembering its
 * first and last position; pre[p] = number of distinct values whose first
 * occurrence is before position p, so every y is answered in O(1).
 * The hash table marks empty slots with max+1, a number that cannot be in A.
 *
 * Input : N, then N integers.      Output: the number of distinct pairs.
 *
 * Sample: 5 / 1 2 2 1 3 -> 6      7 / 1 4 1 2 2 1 3 -> 10
 */
#include <stdio.h>

#define MAXN 200005
#define BITS 19
#define SIZE (1 << BITS)

int arr[MAXN];
int key[SIZE], id[SIZE];
int first[MAXN], last[MAXN];
int pre[MAXN + 1];
char isFirst[MAXN];

int main()
{
    int n, i, max, empty, distinct = 0, h;
    long long ans = 0;

    scanf("%d", &n);
    for(i=0;i<n;i++)
        scanf("%d", &arr[i]);

    max = arr[0];
    for(i=0;i<n;i++)
        if(arr[i]>max)
            max = arr[i];

    /* max + 1 is never a value of the array, so it marks a free slot */
    empty = max + 1;
    for (i = 0; i < SIZE; i++)
        key[i] = empty;

    for (i = 0; i < n; i++)
    {
        h = (int)(((unsigned int)arr[i] * 2654435761u) >> (32 - BITS));
        while (key[h] != empty && key[h] != arr[i])
            h = (h + 1) & (SIZE - 1);
        if (key[h] == empty)
        {
            key[h] = arr[i];
            id[h] = distinct;
            first[distinct] = i;
            isFirst[i] = 1;
            distinct++;
        }
        last[id[h]] = i;
    }

    /* pre[p] = number of distinct values first seen before position p */
    pre[0] = 0;
    for (i = 0; i < n; i++)
        pre[i + 1] = pre[i] + isFirst[i];

    for (i = 0; i < distinct; i++)
        ans += pre[last[i]];

    printf("%lld\n", ans);
    return 0;
}
