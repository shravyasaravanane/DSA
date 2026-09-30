#include <stdio.h>
#define SIZE 5
int arr[SIZE];
int top1=-1,top2=SIZE;
void push1(int x)
{
    if(top1<top2-1)
        arr[++top1]=x;
}
void push2(int x)
{
    if(top1<top2-1)
        arr[--top2]=x;
}
int pop1()
{
    return arr[top1--];
}
int pop2()
{
    return arr[top2++];
}
int main()
{
    int i,x;
    for(i=0;i<5;i++)
    {
        scanf("%d",&x);
        if(i%2==0)
            push1(x);
        else
            push2(x);
    }
    printf("Popped element from stack1 is:%d\n",pop1());
    printf("Popped element from stack2 is:%d\n",pop2());
    return 0;
}