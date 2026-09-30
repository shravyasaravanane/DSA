/*
 * Searching - Horse chariots (Challenge 2)
 * Sort the names alphabetically (ignoring case) but "royal" names go first.
 * A name is royal if one of its words is a gemstone. Royal names are ordered
 * by the highest ranked gem in the name (Lapis is the highest, Garnet the
 * lowest); equal rank -> alphabetical order of the whole name.
 *
 * Gem rank = index in the gems[] table (Garnet=1 ... Lapis=12, NONE=0).
 *
 * Input : names, one per line, until the line END.
 * Output: the sorted list.
 *
 * Sample: Buttershy ... Misty Sapphire END
 *   -> Misty Sapphire, Emerald Sunshine, Buttershy, Orangejack, ...
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXP 105
#define BUFLEN 128

char *gems[]={"NONE","Garnet","Amethyst","Aquamarine","Diamond","Emerald","Pearl","Ruby","Peridot","Sapphire","Tourmaline","Topaz","Lapis",0};
char ponies[MAXP][BUFLEN];
int rank_of[MAXP];

/* case-insensitive compare */
int cmpi(const char *x, const char *y)
{
    while (*x && *y && tolower((unsigned char)*x) == tolower((unsigned char)*y))
    {
        x++;
        y++;
    }
    return tolower((unsigned char)*x) - tolower((unsigned char)*y);
}

/* highest gem rank among the words of the name (0 = not royal) */
int gemRank(char *name)
{
    char copy[BUFLEN];
    char *w;
    int g, best = 0;

    strcpy(copy, name);
    for (w = strtok(copy, " "); w != NULL; w = strtok(NULL, " "))
    {
        for (g = 1; gems[g] != 0; g++)
        {
            if (cmpi(w, gems[g]) == 0 && g > best)
                best = g;
        }
    }
    return best;
}

/* returns 1 if ponies[a] must come AFTER ponies[b] */
int after(int a, int b)
{
    int c;
    if (rank_of[a] != rank_of[b])
    {
        if (rank_of[a] == 0)
            return 1;
        if (rank_of[b] == 0)
            return 0;
        return rank_of[a] < rank_of[b];     /* higher gem first */
    }
    c = cmpi(ponies[a], ponies[b]);
    if (c != 0)
        return c > 0;
    return strcmp(ponies[a],ponies[b])>0;
}

int main()
{
    int n = 0, i, j, tmp;
    int idx[MAXP];
    char line[BUFLEN];

    while (n < MAXP && fgets(line, sizeof(line), stdin) != NULL)
    {
        line[strcspn(line, "\r\n")] = '\0';
        if (strcmp(line, "END") == 0)
            break;
        strcpy(ponies[n], line);
        rank_of[n] = gemRank(ponies[n]);
        idx[n] = n;
        n++;
    }

    /* insertion sort on the index array */
    for (i = 1; i < n; i++)
    {
        tmp = idx[i];
        j = i - 1;
        while (j >= 0 && after(idx[j], tmp))
        {
            idx[j + 1] = idx[j];
            j--;
        }
        idx[j + 1] = tmp;
    }

    for (i = 0; i < n; i++)
        printf("%s\n", ponies[idx[i]]);
    return 0;
}
