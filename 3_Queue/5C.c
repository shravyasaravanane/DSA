#include <stdio.h>
#define MAX 100
int queue[MAX];
int front=-1,rear=-1;
void enqueue(int data)
{
    if(rear==MAX-1)
        return;
    if(front==-1)
        front=0;
    rear++;
    queue[rear]=data;
    printf("Enqueuing %d\n",data);
}
void disp()
{
    int i;
    if(front==-1)
        return;
    for(i=front;i<=rear;i++)
        printf("%d ",queue[i]);
}
int main()
{
    int n,i,data;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&data);
        enqueue(data);
        disp();
    }
    return 0;
}