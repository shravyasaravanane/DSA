/*
 * Hashing - Chocolates with the same number of divisors (Challenge 99)
 * A chocolate of length A[i] can become X = d(A[i]) different types (d =
 * number of divisors). Count the unordered pairs of chocolates with equal X.
 *  1. a linear sieve gives d(n) for all n up to max(A) (<= 10^6);
 *  2. a frequency table indexed by X (X <= 240 for n <= 10^6) counts how
 *     many chocolates have every X;
 *  3. every group of c chocolates gives c*(c-1)/2 pairs (long long: the
 *     answer can reach about 5*10^9).
 *
 * Input : N, then N integers.          Output: the number of pairs.
 *
 * Sample: 3 / 2 3 4 -> 1        10 / 2 3 4 2 7 6 8 6 4 9 -> 12
 */
#include <stdio.h>

#define MAXA 1000005
#define MAXN 100005

int a[MAXN];
int divs[MAXA], primes[80000], freq[1024];
unsigned char e[MAXA];
char composite[MAXA];

int main()
{
    int N, x, cnt = 0, maxv = 1, np = 0, i, j, m;
    long long ans = 0;

    scanf("%d", &N);
    scanf("%d", &x);
    a[cnt++] = x;
    while(--N)
    {
        scanf("%d", &x);
        a[cnt++] = x;
    }

    for (i = 0; i < cnt; i++)
        if (a[i] > maxv)
            maxv = a[i];

    /* linear sieve: divs[n] = number of divisors, e[n] = exponent of the
       smallest prime factor of n */
    divs[1] = 1;
    for (i = 2; i <= maxv; i++)
    {
        if (!composite[i])
        {
            primes[np++] = i;
            divs[i] = 2;
            e[i] = 1;
        }
        for (j = 0; j < np && (long long)i * primes[j] <= maxv; j++)
        {
            m = i * primes[j];
            composite[m] = 1;
            if (i % primes[j] == 0)
            {
                e[m] = e[i] + 1;
                divs[m] = divs[i] / (e[i] + 1) * (e[m] + 1);
                break;
            }
            e[m] = 1;
            divs[m] = divs[i] * 2;
        }
    }

    for (i = 0; i < cnt; i++)
        freq[divs[a[i]]]++;

    for (i = 1; i < 1024; i++)
        ans += (long long)freq[i] * (freq[i] - 1) / 2;

    printf("%lld\n", ans);
    return 0;
}
