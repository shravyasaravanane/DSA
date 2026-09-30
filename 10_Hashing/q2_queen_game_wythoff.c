/*
 * Hashing - Canthi and Sami, the queen game (Challenge 92)
 * The queen moves any number of cells left, up or diagonally up-left and the
 * player who cannot move loses: this is Wythoff's game.
 * The losing positions (P-positions) are the pairs (a_k, b_k) with
 *      a_k = smallest number not used yet,   b_k = a_k + k     (k = 0,1,2..)
 * i.e. (0,0) (1,2) (3,5) (4,7) (6,10) ...
 * They are generated once and stored in a table partner[]: partner[a] = b
 * and partner[b] = a. The position (x, y) with x <= y is losing for the
 * player to move iff partner[x] == y.
 * Canthi moves first, so he wins ("canthi") unless the start is losing
 * ("sami").
 *
 * Input : t, then t lines "a b".       Output: canthi / sami per test case.
 *
 * Sample: 2 / 1 2 / 2 3        -> sami / canthi
 *         3 / 5 6 / 1 5 / 2 3  -> canthi / canthi / canthi
 */
#include <stdio.h>

#define LIMIT 1000000
#define SIZE 2100000

int partner[SIZE];
char used[SIZE];

int main()
{
    int t, x, y, a, k, s;

    /* build the Wythoff pairs up to LIMIT */
    a = 0;
    k = 0;
    while (a <= LIMIT)
    {
        partner[a] = a + k;
        partner[a + k] = a;
        used[a] = 1;
        used[a + k] = 1;
        k++;
        while (used[a])
            a++;
    }

    scanf("%d", &t);
    while(t--)
    {
        scanf("%d %d", &x, &y);
        if (x > y)
        {
            s = x;
            x = y;
            y = s;
        }
        if (partner[x] == y)
            printf("sami\n");
        else
            printf("canthi\n");
    }
    return 0;
}
