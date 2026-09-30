#include <stdio.h>
#include <string.h>
char s[200005];
int pre[800005],suf[800005],best[800005];
void pull(int k,int l,int r)
{
    int m=(l+r)/2,L=2*k,R=2*k+1;
    int lenL=m-l+1,lenR=r-m;
    pre[k]=pre[L];
    suf[k]=suf[R];
    best[k]=best[L];
    if(best[R]>best[k])
        best[k]=best[R];
    if(s[m]==s[m+1])
    {
        if(pre[L]==lenL)
            pre[k]=lenL+pre[R];
        if(suf[R]==lenR)
            suf[k]=lenR+suf[L];
        if(suf[L]+pre[R]>best[k])
            best[k]=suf[L]+pre[R];
    }
}
void build(int k,int l,int r)
{
    if(l==r)
    {
        pre[k]=suf[k]=best[k]=1;
        return;
    }
    int m=(l+r)/2;
    build(2*k,l,m);
    build(2*k+1,m+1,r);
    pull(k,l,r);
}
void update(int k,int l,int r,int pos)
{
    if(l==r)
        return;
    int m=(l+r)/2;
    if(pos<=m)
        update(2*k,l,m,pos);
    else
        update(2*k+1,m+1,r,pos);
    pull(k,l,r);
}
int main()
{
    int n,m,i,x;
    scanf("%s",s);
    n=strlen(s);
    build(1,0,n-1);
    scanf("%d",&m);
    for(i=0;i<m;i++)
    {
        scanf("%d",&x);
        x--;
        if(s[x]=='0')
            s[x]='1';
        else
            s[x]='0';
        update(1,0,n-1,x);
        printf("%d ",best[1]);
    }
    return 0;
}