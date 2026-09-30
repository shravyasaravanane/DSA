#include <stdio.h>
int main()
{
    int n,t;
    scanf("%d",&n);
    int array[n];
    for(int i=0;i<n;i++)
        scanf("%d",&array[i]);
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(array[i]>array[j])
            {
                t=array[i];array[i]=array[j];array[j]=t;
            }
        }
    }
    for(int i=0;i<n-1;i+=2)
    {
        t=array[i];array[i]=array[i+1];array[i+1]=t;
    }
    for(int i=0;i<n;i++)
        printf("%d ",array[i]);
    return 0;
}