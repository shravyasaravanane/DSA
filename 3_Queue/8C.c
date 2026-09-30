#include <stdio.h>
#include <stdlib.h>
typedef struct QNode
{
    struct QNode *prev,*next;
    unsigned pageNumber;
}QNode;
typedef struct Queue
{
    unsigned count;
    unsigned numberOfFrames;
    QNode *front,*rear;
}Queue;
QNode* hash[1000];
QNode* newQNode(unsigned pageNumber)
{
    QNode* temp=(QNode*)malloc(sizeof(QNode));
    temp->pageNumber=pageNumber;
    temp->prev=NULL;
    temp->next=NULL;
    return temp;
}
Queue* createQueue(int numberOfFrames)
{
    Queue* queue=(Queue*)malloc(sizeof(Queue));
    queue->count=0;
    queue->front=NULL;
    queue->rear=NULL;
    queue->numberOfFrames=numberOfFrames;
    return queue;
}
void dequeue(Queue* queue)
{
    QNode* temp=queue->rear;
    if(queue->rear==NULL)
        return;
    if(queue->front==queue->rear)
        queue->front=NULL;
    queue->rear=queue->rear->prev;
    if(queue->rear!=NULL)
        queue->rear->next=NULL;
    hash[temp->pageNumber]=NULL;
    free(temp);
    queue->count--;
}
void enqueue(Queue* queue,unsigned pageNumber)
{
    QNode* temp;
    if(queue->count==queue->numberOfFrames)
        dequeue(queue);
    temp=newQNode(pageNumber);
    temp->next=queue->front;
    if(queue->rear==NULL)
    {
        queue->front=temp;
        queue->rear=temp;
    }
    else
    {
        queue->front->prev=temp;
        queue->front=temp;
    }
    hash[pageNumber]=temp;
    queue->count++;
}
void referencePage(Queue* queue,unsigned pageNumber)
{
    QNode* req=hash[pageNumber];
    if(req==NULL)
        enqueue(queue,pageNumber);
    else if(req!=queue->front)
    {
        req->prev->next=req->next;
        if(req->next!=NULL)
            req->next->prev=req->prev;
        if(req==queue->rear)
        {
            queue->rear=req->prev;
            queue->rear->next=NULL;
        }
        req->next=queue->front;
        req->prev=NULL;
        queue->front->prev=req;
        queue->front=req;
    }
}
int main()
{
    int n,m,i,x;
    QNode* temp;
    scanf("%d %d",&n,&m);
    Queue* q=createQueue(m);
    for(i=0;i<n;i++)
    {
        scanf("%d",&x);
        referencePage(q,x);
    }
    temp=q->front;
    while(temp!=NULL)
    {
        printf("%d ",temp->pageNumber);
        temp=temp->next;
    }
    return 0;
}