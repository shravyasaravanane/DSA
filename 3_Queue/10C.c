#include <stdio.h>
#define MAX 100
int queue[MAX];
int front=-1,rear=-1;
void enqueue(int data,int l)
{
    if(rear==l-1)
        return;
    if(front==-1)
        front=0;
    queue[++rear]=data;
}
void reverse()
{
    int i,j,t;
    for(i=front,j=rear;i<j;i++,j--)
    {
        t=queue[i];
        queue[i]=queue[j];
        queue[j]=t;
    }
}
void display()
{
    int i;
    for(i=front;i<=rear;i++)
        printf("%d ",queue[i]);
    printf("\n");
}
int main()
{
    int n,i,t;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&t);
        enqueue(t,n);
    }
    printf("Queue:");
    display();
    reverse();
    printf("Reversed Queue:");
    display();
    return 0;
}