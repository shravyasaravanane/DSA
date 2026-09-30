#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node* next;
};
typedef struct
{
    struct node* head;
    struct node* tail;
}mystack;
void push(int data, mystack* ms)
{
    struct node* temp=(struct node*)malloc(sizeof(struct node));
    temp->data=data;
    temp->next=ms->head;
    if(ms->head==NULL)
        ms->tail=temp;
    ms->head=temp;
}
int pop(mystack* ms)
{
    struct node* temp=ms->head;
    int x=temp->data;
    ms->head=temp->next;
    free(temp);
    return x;
}
void merge(mystack* ms1, mystack* ms2)
{
    if(ms1->head==NULL)
    {
        ms1->head=ms2->head;
        ms1->tail=ms2->tail;
    }
    else
    {
        ms1->tail->next=ms2->head;
        ms1->tail=ms2->tail;
    }
}
int main()
{
    int n,m,i,x;
    mystack s1,s2;
    s1.head=NULL;s1.tail=NULL;
    s2.head=NULL;s2.tail=NULL;
    scanf("%d %d",&n,&m);
    for(i=0;i<n;i++)
    {
        scanf("%d",&x);
        push(x,&s1);
    }
    for(i=0;i<m;i++)
    {
        scanf("%d",&x);
        push(x,&s2);
    }
    merge(&s1,&s2);
    while(s1.head!=NULL)
        printf("%d ",pop(&s1));
    return 0;
}