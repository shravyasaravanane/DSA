#include <stdio.h>
int main()
{
    int n,i,j,f,g;
    scanf("%d",&n);
    long long a[n];
    for(i=0;i<n;i++)
        scanf("%lld",&a[i]);
    for(i=0;i<n;i++)
    {
        f=-1;
        g=-1;
        for(j=i+1;j<n;j++)
        {
            if(a[j]>a[i])
            {
                f=j;
                break;
            }
        }
        if(f!=-1)
        {
            for(j=f+1;j<n;j++)
            {
                if(a[j]<a[f])
                {
                    g=j;
                    break;
                }
            }
        }
        if(g==-1)
            printf("-1 ");
        else
            printf("%lld ",a[g]);
    }
    return 0;
}