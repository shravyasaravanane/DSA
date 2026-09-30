/*
 * Hashing - Triplets whose sum is divisible by M (Challenge 100)
 * Count the triples of positions i < j < k with (A[i]+A[j]+A[k]) % M == 0.
 * Only residues matter, so cnt[r] = how many elements have A % M == r
 * (a table indexed by the residue). Every triple of residues a <= b <= c
 * with a+b+c = 0 (mod M) contributes
 *      all equal        : C(cnt,3)
 *      two equal        : C(cnt[x],2) * cnt[y]
 *      all different    : cnt[a] * cnt[b] * cnt[c]
 * For a fixed smallest residue a, the pairs (b, c) with b + c equal to a
 * target sum s are found with two pointers i (from a) and k (from M-1):
 *      while(i<k) { move the pointer that brings i+k closer to s }
 * s can only be (M-a)%M or that plus M, so the whole work is O(M^2) <= 2*10^8
 * simple steps, independent of N. The answer needs long long (~10^15).
 *
 * Input : N M, then N integers.        Output: the number of triplets.
 *
 * Sample: 10 5 / 1 10 4 3 2 5 0 1 9 5 -> 26
 *         10 5 / 11 10 14 31 21 15 10 11 9 51 -> 31
 */
#include <stdio.h>

#define MAXM 10005

long long cnt[MAXM];

long long C2(long long x)
{
    return x * (x - 1) / 2;
}

long long C3(long long x)
{
    return x * (x - 1) * (x - 2) / 6;
}

/* number of position triples with residues a <= b <= c */
long long ways(int a, int b, int c)
{
    if (a == b && b == c)
        return C3(cnt[a]);
    if (a == b)
        return C2(cnt[a]) * cnt[c];
    if (b == c)
        return cnt[a] * C2(cnt[b]);
    return cnt[a] * cnt[b] * cnt[c];
}

int main()
{
    int n, M, i, k, a, x, s, t, target[2];
    long long total = 0;

    scanf("%d %d", &n, &M);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &x);
        cnt[x % M]++;
    }

    for (a = 0; a < M; a++)
    {
        if (cnt[a] == 0)
            continue;
        target[0] = (M - a) % M;
        target[1] = target[0] + M;
        for (t = 0; t < 2; t++)
        {
            s = target[t];
            i = a;
            k = M - 1;
            while(i<k)
            {
                if (i + k == s)
                {
                    if (cnt[i] && cnt[k])
                        total += ways(a, i, k);
                    i++;
                    k--;
                }
                else if (i + k < s)
                    i++;
                else
                    k--;
            }
            /* the case b == c */
            if (s % 2 == 0 && s / 2 >= a && s / 2 < M && cnt[s / 2])
                total += ways(a, s / 2, s / 2);
        }
    }
    printf("%lld\n", total);
    return 0;
}
