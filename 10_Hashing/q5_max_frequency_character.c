/*
 * Hashing - Character with the maximum occurrence (Challenge 95)
 * The line may contain letters, digits, spaces and symbols. Every character
 * is hashed into a table of 256 counters (its ASCII code is the hash). The
 * answer is the character with the largest counter; on a tie the smaller
 * ASCII value wins, which happens naturally when the table is scanned from
 * 0 to 255 and only a strictly larger count replaces the best one.
 *
 * Input : one line (length <= 1000).   Output: "character count".
 *
 * Sample: puppy is a dog!!!!!!!!!!!!  ->  ! 12
 *         aaaaAAAA                    ->  A 4
 */
#include <stdio.h>
#include <string.h>

int main()
{
    char s[2050];
    int count[256] = {0};
    int i, l, best = 0;

    if (fgets(s, sizeof(s), stdin) == NULL)
        return 0;
    l = strlen(s);
    while (l > 0 && (s[l - 1] == '\n' || s[l - 1] == '\r'))
        s[--l] = '\0';

    for(i=0;i<l;i++)
        count[(unsigned char)s[i]]++;

    for (i = 1; i < 256; i++)
        if (count[i] > count[best])
            best = i;

    printf("%c %d\n", best, count[best]);
    return 0;
}
