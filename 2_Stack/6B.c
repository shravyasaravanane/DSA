#include <stdio.h>
void calculateSpan(int price[],int n,int S[])
{
    int i,j;
    for(i=0;i<n;i++)
    {
        S[i]=1;
        j=i-1;
        while(j>=0&&price[j]<=price[i])
        {
            S[i]++;
            j--;
        }
    }
}
void printArray(int arr[],int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d ",arr[i]);
}
int main()
{
    int n,i;
    scanf("%d",&n);
    int price[n],S[n];
    for(i=0;i<n;i++)
        scanf("%d",&price[i]);
    calculateSpan(price,n,S);
    printArray(S,n);
    return 0;
}