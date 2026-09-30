#include <stdio.h>
#define MAXN 105
#define read(x) scanf("%d",&x)
int s[MAXN];
void sol()
{
    int n,i,j,t,total=0,rank=1;
    read(n);
    for(i=0;i<n;i++)
        read(s[i]);
    for(i=0;i<n;i++)
        for(j=i+1;j<n;j++)
            if(s[i]>s[j])
            {
                t=s[i];s[i]=s[j];s[j]=t;
            }
    for(i=0;i<n;i++)
    {
        if(i>0&&s[i]!=s[i-1])
            rank++;
        total+=rank;
    }
    printf("%d\n",total);
}
int main()
{
    int t;
    read(t);
    while(t--)
        sol();
    return 0;
}