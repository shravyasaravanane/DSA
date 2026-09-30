#include <stdio.h>
#define MAX 10
#define LEN 100
int main()
{
    char name[MAX][LEN];
    int price[MAX];
    int afford[MAX]={0},used[MAX]={0};
    int money,items,i,k,min,count=0;
    scanf("%d %d",&money,&items);
    for(i=0;i<items;i++)
        scanf("%s %d",name[i],&price[i]);
    for(k=0;k<items;k++)
    {
        min=-1;
        for(i=0;i<items;i++)
            if(used[i]==0&&(min==-1||price[i]<price[min]))
                min=i;
        used[min]=1;
        if(price[min]<=money)
        {
            money-=price[min];
            afford[min]=1;
            count++;
        }
    }
    for(i=0;i<items;i++)
    {
        if(afford[i]==1)
            printf("I can afford %s\n",name[i]);
        else
            printf("I can't afford %s\n",name[i]);
    }
    if(count==0)
        printf("I need more Dollar!\n");
    else
        printf("%d\n",money);
    return 0;
}