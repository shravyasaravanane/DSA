/*
 * Searching - Painting the building (Challenge 5)
 * M sections with beauty scores (digits). Nesamani paints a connected
 * block that grows one section per day while the building is destroyed
 * from the ends. He can always secure a block of ceil(M/2) sections, and
 * the adversary decides which such block survives, so the best guaranteed
 * value is the maximum sum of any window of ceil(M/2) consecutive digits.
 *
 * Idea: prefix sums b[0..M] and a sliding window of length (M+1)/2.
 * (The original solution uses  vector<int> b(N+1);  in C++ - in C this is
 *  the plain array b[] below.)
 *
 * Input : T, then for every case: M and a string of M digits.
 * Output: the maximum guaranteed beauty for every case.
 *
 * Sample: 4 / 1332 -> 6 ; 4 / 9583 -> 14 ; 3 / 616 -> 7 ;
 *         10 / 1029384756 -> 31
 */
#include <stdio.h>

int main()
{
    int T, k, N, i, w, best, cur;
    char s[128];
    int b[128];     /* C form of: vector<int> b(N+1); */

    scanf("%d", &T);
    for(k=1;k<=T;++k)
    {
        scanf("%d", &N);
        scanf("%s", s);

        b[0] = 0;
        for (i = 0; i < N; i++)
            b[i + 1] = b[i] + (s[i] - '0');

        w = (N + 1) / 2;            /* ceil(N / 2) */
        best = 0;
        for (i = w; i <= N; i++)
        {
            cur = b[i] - b[i - w];
            if (cur > best)
                best = cur;
        }
        printf("%d\n", best);
    }
    return 0;
}
