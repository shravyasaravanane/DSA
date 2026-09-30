#include <stdio.h>
#include <stdlib.h>
int main()
{
    char nums[13][256]={"ZERO","ONE","TWO","THREE","FOUR","FIVE","SIX","SEVEN","EIGHT","NINE","TEN","ELEVEN","TWELVE"};
    char s[20];
    int cnt[26]={0},n,k,i,first=1;
    while(scanf("%s",s)==1)
    {
        if(first==0)
            printf(" ");
        printf("%s",s);
        first=0;
        k=atoi(s);
        if(k==999)
            break;
        if(k>=0&&k<=12)
            for(i=0;nums[k][i]!='\0';i++)
                cnt[nums[k][i]-'A']++;
    }
    printf(". ");
    first=1;
    for(n=0;n<26;n++)
    {
        for(i=0;i<cnt[n];i++)
        {
            if(first==0)
                printf(" ");
            printf("%c",'A'+n);
            first=0;
        }
    }
    return 0;
}