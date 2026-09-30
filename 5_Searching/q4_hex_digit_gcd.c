/*
 * Searching - GCD with hexadecimal digit sum (Challenge 4)
 * F(X) = sum of the digits of X written in base 16   (F(27)=1+B=12).
 * For every query [L, R] count the integers X with GCD(X, F(X)) > 1.
 *
 * Idea: R <= 10^5, so precompute good[X] once and build prefix counts
 * pre[X]. Every query is then answered in O(1):  pre[b] - pre[a-1].
 *
 * Input : T, then T lines "L R".
 * Output: the count for every query.
 *
 * Sample: 3 / 1 3 / 5 8 / 7 12  -> 2 4 6
 */
#include <stdio.h>

#define MAXN 100000

int pre[MAXN + 1];

int gcd(int a, int b)
{
    while (b != 0)
    {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int hexSum(int x)
{
    int s = 0;
    while (x > 0)
    {
        s += x % 16;
        x /= 16;
    }
    return s;
}

/* number of integers in [a, b] satisfying the condition */
int search(int a, int b)
{
    return pre[b] - pre[a - 1];
}

int main()
{
    int t, l, r, x;

    pre[0] = 0;
    for (x = 1; x <= MAXN; x++)
        pre[x] = pre[x - 1] + (gcd(x, hexSum(x)) > 1 ? 1 : 0);

    scanf("%d", &t);
    while (t-- > 0)
    {
        scanf("%d %d", &l, &r);
        printf("%d\n", search(l, r));
    }
    return 0;
}
