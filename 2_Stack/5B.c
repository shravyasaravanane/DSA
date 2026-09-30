#include <stdio.h>
char stack[1000];
int top=-1;
void push(char c)
{
    stack[++top]=c;
}
char pop()
{
    return stack[top--];
}
int empty()
{
    return top==-1;
}
int main()
{
    char s[1000],c;
    int i,ok=1;
    scanf("%s",s);
    for(i=0;s[i]!='\0';i++)
    {
        if(s[i]=='('||s[i]=='{'||s[i]=='[')
            push(s[i]);
        else
        {
            if(empty())
            {
                ok=0;
                break;
            }
            c=pop();
            if((s[i]==')'&&c!='(')||(s[i]=='}'&&c!='{')||(s[i]==']'&&c!='['))
            {
                ok=0;
                break;
            }
        }
    }
    if(ok==1&&empty())
        printf("Balanced");
    else
        printf("Not Balanced");
    return 0;
}