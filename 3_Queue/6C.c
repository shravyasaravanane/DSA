#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int data;
    struct Node* link;
};
typedef struct Queue
{
    struct Node *front,*rear;
}Queue;
void enQueue(Queue* q,int value)
{
    struct Node* temp=(struct Node*)malloc(sizeof(struct Node));
    temp->data=value;
    if(q->front==NULL)
        q->front=temp;
    else
        q->rear->link=temp;
    q->rear=temp;
    q->rear->link=q->front;
}
int deQueue(Queue* q)
{
    int value;
    struct Node* temp;
    if(q->front==NULL)
        return -1;
    value=q->front->data;
    if(q->front==q->rear)
    {
        free(q->front);
        q->front=NULL;
        q->rear=NULL;
    }
    else
    {
        temp=q->front;
        q->front=q->front->link;
        q->rear->link=q->front;
        free(temp);
    }
    return value;
}
void displayQueue(struct Queue* q)
{
    struct Node* temp=q->front;
    printf("Elements in Circular Queue are:");
    if(temp==NULL)
        return;
    while(temp->link!=q->front)
    {
        printf("%d ",temp->data);
        temp=temp->link;
    }
    printf("%d",temp->data);
}
int main()
{
    int n,i,x;
    Queue q;
    q.front=NULL;
    q.rear=NULL;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&x);
        enQueue(&q,x);
    }
    displayQueue(&q);
    printf("\nDeleted value = %d",deQueue(&q));
    printf("\nDeleted value = %d",deQueue(&q));
    displayQueue(&q);
    return 0;
}