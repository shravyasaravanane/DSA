#include <stdio.h>
int a[100005];
int main()
{
    int n,i;
    long long biggest=-1,big=-1,small=-1,t;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
        if(a[i]>biggest)
        {
            small=big;
            big=biggest;
            biggest=a[i];
        }
        else
        {
            if(a[i]>small)
                small=a[i];
            if(big<small)
            {
                t=big;big=small;small=t;
            }
            if(biggest<big)
            {
                t=biggest;biggest=big;big=t;
            }
        }
        if(i<2)
            printf("-1\n");
        else
            printf("%lld\n",biggest*big*small);
    }
    return 0;
}