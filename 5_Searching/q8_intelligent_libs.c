/*
 * Searching - Intelligent libs (Challenge 8)
 * Line 1 is the story containing placeholders:
 *      [N] noun   [AV] adverb   [V] verb   [AJ] adjective
 * Then the word lists follow, each one starting with its heading:
 *      NOUNS, ADVERBS, VERBS, ADJECTIVES  and finally END.
 * The story is printed TWICE; for every placeholder the top-most unused
 * word of its list is used (a word is never reused).
 *
 * Idea: lists[c][k] holds the k-th word of list c, cl[c] counts the words
 * and used[t] is the cursor of the next unused word of token t.
 *
 * Sample: There once was a [AJ] [N] from [N] who [AV] [V] all day. ...
 *   -> There once was a delightful squirrel from London who silently skipped all day.
 *      There once was a homely tree from lettuce who quickly ran all day.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMDS 5
#define TOKENS 4
#define MAXWORDS 100
#define LINELEN 1024

char *tokens[TOKENS]={"[N]","[AV]","[V]","[AJ]"};
char *cmds[CMDS]={"NOUNS","ADVERBS","VERBS","ADJECTIVES","END"};
char *lists[CMDS][MAXWORDS];
int cl[CMDS]={0};
int used[CMDS]={0};

int main()
{
    char story[LINELEN], line[LINELEN];
    int cur = -1, i, t, pass, matched;
    char *p;

    if (fgets(story, sizeof(story), stdin) == NULL)
        return 0;
    story[strcspn(story, "\r\n")] = '\0';

    while (fgets(line, sizeof(line), stdin) != NULL)
    {
        line[strcspn(line, "\r\n")] = '\0';
        /* trim trailing spaces */
        i = strlen(line);
        while (i > 0 && line[i - 1] == ' ')
            line[--i] = '\0';
        if (line[0] == '\0')
            continue;

        for (i = 0; i < CMDS; i++)
            if (strcmp(line, cmds[i]) == 0)
                break;

        if (i == CMDS)                       /* an ordinary word */
        {
            if (cur >= 0 && cl[cur] < MAXWORDS)
            {
                lists[cur][cl[cur]] = (char *)malloc(strlen(line) + 1);
                strcpy(lists[cur][cl[cur]], line);
                cl[cur]++;
            }
        }
        else if (i == CMDS - 1)              /* END */
            break;
        else
            cur = i;                         /* heading: switch list */
    }

    /* token t uses list t : [N]->NOUNS, [AV]->ADVERBS, [V]->VERBS, [AJ]->ADJECTIVES */
    for (pass = 0; pass < 2; pass++)
    {
        p = story;
        while (*p != '\0')
        {
            matched = 0;
            for (t = 0; t < TOKENS; t++)
            {
                int len = strlen(tokens[t]);
                if (strncmp(p, tokens[t], len) == 0)
                {
                    if (used[t] < cl[t])
                        printf("%s", lists[t][used[t]++]);
                    p += len;
                    matched = 1;
                    break;
                }
            }
            if (!matched)
            {
                putchar(*p);
                p++;
            }
        }
        printf("\n");
    }
    return 0;
}
