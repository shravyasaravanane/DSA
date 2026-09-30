/*
 * Hashing - Alice and the festivals (Challenge 93)
 * For every festival name only the three biggest spendings are remembered.
 * Print the festival with the biggest remembered total; on a tie the
 * lexicographically smallest name.
 *
 * A hash table (open addressing, key = festival name) stores for every
 * festival its top three spendings a >= b >= c. Every new spending x is
 * inserted into the three slots in O(1). At the end the table is scanned
 * for the best total (strcmp gives the lexicographic tie break; names are
 * case sensitive, upper case letters come first).
 *
 * Input : T, then per test case: N and N lines "name spending".
 * Output: "name total" per test case.
 *
 * Sample: 2 / 6 / B 20 / A 2 / A 10 / A 10 / B 30 / A 30 / 3 / abc 10 /
 *         xyz 15 / oop 8   ->  A 50 / xyz 15
 */
#include <stdio.h>
#include <string.h>

#define SIZE 32768

struct festival
{
    char name[16];
    long long a, b, c;     /* three biggest spendings */
    int used;
};

struct festival table[SIZE];

int hash(char s[])
{
    unsigned int h = 5381;
    int i;
    for (i = 0; s[i]; i++)
        h = h * 33 + (unsigned char)s[i];
    return h & (SIZE - 1);
}

int main()
{
    int t, n, i, h, best;
    long long x, total, bestTotal;
    char name[16];

    scanf("%d", &t);
    while(t--)
    {
        for (i = 0; i < SIZE; i++)
            table[i].used = 0;

        scanf("%d", &n);
        for (i = 0; i < n; i++)
        {
            scanf("%15s %lld", name, &x);
            h = hash(name);
            while (table[h].used && strcmp(table[h].name, name) != 0)
                h = (h + 1) & (SIZE - 1);
            if (!table[h].used)
            {
                table[h].used = 1;
                strcpy(table[h].name, name);
                table[h].a = table[h].b = table[h].c = 0;
            }
            if (x > table[h].a)
            {
                table[h].c = table[h].b;
                table[h].b = table[h].a;
                table[h].a = x;
            }
            else if (x > table[h].b)
            {
                table[h].c = table[h].b;
                table[h].b = x;
            }
            else if (x > table[h].c)
                table[h].c = x;
        }

        best = -1;
        bestTotal = -1;
        for (i = 0; i < SIZE; i++)
        {
            if (!table[i].used)
                continue;
            total = table[i].a + table[i].b + table[i].c;
            if (total > bestTotal ||
                (total == bestTotal && strcmp(table[i].name, table[best].name) < 0))
            {
                best = i;
                bestTotal = total;
            }
        }
        printf("%s %lld\n", table[best].name, bestTotal);
    }
    return 0;
}
