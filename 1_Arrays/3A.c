#include <stdio.h>
int main()
{
    int t,n,i,arr[20],start,end,run,found;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(i=0;i<n;i++)
            scanf("%d",&arr[i]);
        run=0;found=0;start=0;end=0;
        for(i=1;i<n;i++)
        {
            if(arr[i]>arr[i-1])
            {
                if(run==0){start=i-1;run=1;}
                end=i;
            }
            else if(run==1)
            {
                printf("(%d %d)",start,end);
                run=0;found=1;
            }
        }
        if(run==1){printf("(%d %d)",start,end);found=1;}
        if(found==0)
            printf("No Profit");
        printf("\n");
    }
    return 0;
}