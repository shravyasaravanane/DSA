#include <stdio.h>
int arr[100005],arr2[100005];
int main()
{
    int n,q,i,x,y,ans,num,sum;
    scanf("%d %d",&n,&q);
    for(i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
        num=arr[i];
        sum=0;
        while(num>0)
        {
            sum+=num%10;
            num/=10;
        }
        arr2[i]=sum;
    }
    for(i=0;i<q;i++)
    {
        int k=0;
        scanf("%d",&k);
        ans=-1;
        if(k>=1&&k<=n)
        {
            x=k-1;
            for(y=x+1;y<n;y++)
            {
                if(arr[x]<arr[y])
                {
                    if(arr2[x]>arr2[y])
                    {
                        ans=y+1;
                        break;
                    }
                }
            }
        }
        printf("%d ",ans);
    }
    return 0;
}