#include <stdio.h>
int a[1000000];
int main()
{
    int n,i,j,k;
    scanf("%d",&n);
    for(k=0;k<n;k++)
        scanf("%d",&a[k]);
    i=0;
    j=n-1;
    while(i<n&&j>=0)
    {
        if(a[i]>a[j])
        {
            printf("1 ");
            j--;
        }
        else if(a[i]<a[j])
        {
            printf("2 ");
            i++;
        }
        else
        {
            printf("0 ");
            i++;
            j--;
        }
    }
    return 0;
}