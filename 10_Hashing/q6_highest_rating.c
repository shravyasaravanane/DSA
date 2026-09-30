/*
 * Hashing - Highest possible rating of an array (Challenge 96)
 * Every element A[i] can be changed to A[i] + j*M for any j in -Q..Q (at
 * most Q additions or subtractions of M). The rating is the highest
 * frequency of a value, so we want the value reachable from the most
 * elements.
 * Each element reaches 2Q+1 different values, so it adds one to the counter
 * of each of them in a frequency table hash[] (direct addressing; values go
 * from 1-M*Q up to 10^6+M*Q, so the table pointer is shifted by an offset
 * to allow the small negative indices). The largest counter is the answer.
 * Work: N*(2Q+1) <= 2.1*10^7 operations.
 *
 * Input : M, Q, N, then the N elements.     Output: the highest rating.
 *
 * Sample: 1 / 1 / 4 / 1 2 3 4            -> 3
 *         1 / 1 / 5 / 11 12 31 41 51     -> 2
 */
#include <stdio.h>

#define MAXN 1000005
#define OFFSET 1024

int A[MAXN];
int counter[1000000 + 2 * OFFSET + 16];

int main()
{
    int M, Q, N, i, j, base, best = 0;
    int *hash = counter + OFFSET;   /* hash[-OFFSET] .. are valid */

    scanf("%d %d %d", &M, &Q, &N);
    for(i=0;i<N;i++)
        scanf("%d", &A[i]);

    for(i=0;i<N;i++)
    {
        base = A[i];
        A[i] = base - Q * M;             /* smallest reachable value */
        for (j = -Q; j <= Q; j++)
        {
            hash[A[i]]++;
            if (hash[A[i]] > best)
                best = hash[A[i]];
            A[i] += M;
        }
        A[i] = base;
    }

    printf("%d\n", best);
    return 0;
}
