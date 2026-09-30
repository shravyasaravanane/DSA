#include <stdio.h>
char a[1001][1001];
int main()
{
    int p,q,i,j,top,bottom,left,right;
    char ch='Y';
    scanf("%d %d",&p,&q);
    top=0;bottom=p-1;left=0;right=q-1;
    while(top<=bottom && right>=left)
    {
        for(j=left;j<=right;j++){a[top][j]=ch;a[bottom][j]=ch;}
        for(i=top;i<=bottom;i++){a[i][left]=ch;a[i][right]=ch;}
        top++;bottom--;left++;right--;
        if(ch=='Y')
            ch='0';
        else
            ch='Y';
    }
    for(i=0;i<p;i++)
    {
        for(j=0;j<q;j++)
            printf("%c ",a[i][j]);
        printf("\n");
    }
    return 0;
}