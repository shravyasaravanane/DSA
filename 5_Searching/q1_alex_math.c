/*
 * Searching - Alex and the math (Challenge 1)
 * The three variables are related by  M = -D * X.
 * Every input line is "<capital letter> <value>" where exactly one value is
 * a question mark. Find the missing variable:
 *      M = -D * X        D = -M / X        X = -M / D
 * Output: the variable name in small letter, a space, the value (2 decimals).
 *
 * Input : 3 lines (M, D, X in any order), one of them has '?'.
 * Output: e.g.  x 2.92
 *
 * Sample: M 14.00 / D -4.80 / X ?  -> x 2.92
 *         M 12.00 / D -5.80 / X ?  -> x 2.07
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 32

int main()
{
    char var[3][LEN];
    char inp[3][LEN];
    double m = 0, d = 0, x = 0, res = 0;
    int i, unknown = -1;

    for (i = 0; i < 3; i++)
    {
        scanf("%s %s", var[i], inp[i]);
        if (inp[i][0] == '?')
        {
            unknown = i;
            continue;
        }
        if (var[i][0] == 'M')
            m = atof(inp[i]);
        else if (var[i][0] == 'D')
            d = atof(inp[i]);
        else
            x = atof(inp[i]);
    }

    if (unknown == -1)
        return 0;

    if (var[unknown][0] == 'M')
        res = -d * x;
    else if (var[unknown][0] == 'D')
        res = (x != 0) ? -m / x : 0;
    else
        res = (d != 0) ? -m / d : 0;

    if (res == 0)       /* avoid printing -0.00 */
        res = 0;

    printf("%c %.2f\n", var[unknown][0] + 32, res);
    return 0;
}
