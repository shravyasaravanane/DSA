#include <stdio.h>
int main()
{
    int r,c,m,n,k;
    scanf("%d %d",&r,&c);
    int arr[r][c];
    int arrTemp[r][c];
    for(m=0;m<r;m++)
        for(n=0;n<c;n++)
        {
            scanf("%d",&arr[m][n]);
            arrTemp[m][n]=arr[m][n];
        }
    for(m=0;m<r;m++)
    {
        for(n=0;n<c;n++)
        {
            if(arr[m][n]==1)
            {
                for(k=0;k<c;k++)
                    arrTemp[m][k]=1;
                for(k=0;k<r;k++)
                    arrTemp[k][n]=1;
            }
        }
    }
    for(m=0;m<r;m++)
    {
        for(n=0;n<c;n++)
            printf("%d ",arrTemp[m][n]);
        printf("\n");
    }
    return 0;
}