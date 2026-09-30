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
    queue[++rear]=data;
}
void dequeue()
{
    if(front==-1||front>rear)
        return;
    front++;
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
    int n,i,data;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&data);
        enqueue(data);
    }
    printf("Dequeuing elements:\n");
    for(i=0;i<n-1;i++)
    {
        dequeue();
        display();
    }
    return 0;
}