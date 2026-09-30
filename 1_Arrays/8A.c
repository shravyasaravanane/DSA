#include <stdio.h>
int main()
{
    int t,m,n,i,j,x1,y1,x2,y2;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d",&m,&n);
        int C[m][n];
        for(i=0;i<m;i++)
            for(j=0;j<n;j++)
                scanf("%d",&C[i][j]);
        scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
        long long sum=0;
        for(i=0;i<m;i++)
            for(j=0;j<n;j++)
                if(i>=x1-1&&i<=x2-1&&j>=y1-1&&j<=y2-1)
                    sum+=C[i][j];
        printf("%lld\n",sum);
    }
    return 0;
}