#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node* next;
};
struct node *f = NULL;
struct node *r = NULL;
void enqueue(int d)
{
    struct node* n;
    n = (struct node*)malloc(sizeof(struct node));
    n->data = d;
    n->next = NULL;
    if(f==NULL)
    {
        f=n;
        r=n;
    }
    else
    {
        r->next=n;
        r=n;
    }
    r->next=f;
}
void dequeue()
{
    struct node* t;
    if(f==NULL)
        return;
    t=f;
    if(f==r)
    {
        f=NULL;
        r=NULL;
    }
    else
    {
        f=f->next;
        r->next=f;
    }
    free(t);
}
void display()
{
    struct node* t;
    if(f==NULL)
        return;
    t=f;
    do
    {
        printf("%d\n",t->data);
        t=t->next;
    }while(t!=f);
}
int main()
{
    int n,i,x;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&x);
        enqueue(x);
    }
    display();
    return 0;
}