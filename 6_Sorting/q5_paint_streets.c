/*
 * Sorting - Paint the streets (Challenge 15)
 * Each street is a segment [Xl, Xr] on the X axis. Priya chooses some of
 * the streets and paints them green. The painted streets must form one
 * continuous green segment whose length is exactly L.
 *
 * Idea: sort the streets by their left border. Try every street's left
 * border 'a' as the start of the green segment, so the segment must be
 * [a, a+L]. Take all streets that lie completely inside [a, a+L] and
 * check (with a sweep over the sorted streets) that together they cover
 * [a, a+L] without a gap.
 *
 * Input : T, then for every test case: N L and N lines "Xl Xr".
 * Output: "Yes" if it is possible, otherwise "No".
 *
 * Sample: 5 3 / 1 2 / 2 3 / 3 4 / 1 5 / 2 6  -> Yes
 *         2 3 / 1 2 / 2 6                     -> No
 */
#include <stdio.h>

typedef long long ll;

/* insertion sort of the streets by their left border */
void sortStreets(ll xl[], ll xr[], ll n)
{
    ll i, j, keyL, keyR;
    for (i = 1; i < n; i++)
    {
        keyL = xl[i];
        keyR = xr[i];
        j = i - 1;
        while (j >= 0 && xl[j] > keyL)
        {
            xl[j + 1] = xl[j];
            xr[j + 1] = xr[j];
            j--;
        }
        xl[j + 1] = keyL;
        xr[j + 1] = keyR;
    }
}

int main()
{
    int t;
    ll n, L, tmp;
    ll xl[2005], xr[2005];

    scanf("%d", &t);
    while(t--)
    {
        scanf("%lld %lld", &n, &L);
        for(ll i=0;i<n;i++)
        {
            scanf("%lld %lld", &xl[i], &xr[i]);
            if (xl[i] > xr[i])          /* make sure Xl <= Xr */
            {
                tmp = xl[i];
                xl[i] = xr[i];
                xr[i] = tmp;
            }
        }

        sortStreets(xl, xr, n);

        int possible = 0;
        for(ll i=0;i<n && !possible;i++)
        {
            ll a = xl[i];
            ll maxright = a + L;     /* the green segment is [a, maxright] */
            ll cur_right = a;        /* how far the green paint reaches    */

            for(ll j=0;j<n;j++)
            {
                if (xl[j] < a || xr[j] > maxright)
                    continue;        /* street is not inside [a, a+L]      */
                if (xl[j] > cur_right)
                    break;           /* gap: the paint is not continuous   */
                if (xr[j] > cur_right)
                    cur_right = xr[j];
            }

            if(cur_right==maxright)
                possible = 1;
        }

        printf(possible ? "Yes\n" : "No\n");
    }
    return 0;
}
