#include <iostream>
#include <malloc.h>
using namespace std;

typedef int DataType;
struct QNode
{
    DataType data;
    struct QNode *link;
};
typedef struct QNode *PNode;

//r为低 f为顶
struct LinkQueue
{
    PNode f;
    PNode r;
};
typedef struct LinkQueue * PLinkQueue;

PLinkQueue createEmptyQueue()
{
    PLinkQueue plqueue = (PLinkQueue) malloc (sizeof(struct LinkQueue));
    if(plqueue != NULL)
    {
        plqueue ->f = NULL;
        plqueue ->r =NULL;
    }
    else
        printf("Out of space\n");
    return plqueue;
}

int isEmptyQueue(PLinkQueue plqueue)
{
    return (plqueue ->f == NULL);
}

void enQueue( PLinkQueue plqueue, DataType x)
{
    PNode p = (PNode) malloc (sizeof(struct QNode));
    if(p!= NULL)
    {
        p->data = x;
        p->link = NULL;

        if(plqueue ->f == NULL)
            plqueue->f = p;
        else
            plqueue ->r -> link = p;

        plqueue->r =p;
    }
    else
        printf("Out of space\n");

}

void deQueue(PLinkQueue plqueue)
{
    PNode p = (PNode) malloc (sizeof(struct QNode));
    if(plqueue->f == NULL)
        printf("Empty Queue\n");
    else
    {
        p = plqueue ->f;
        plqueue -> f = p ->link;
        free(p);
    }

}

DataType getFront(PLinkQueue plqueue)
{
    if(plqueue ->f == NULL)
        printf("Empty Queue\n");
    else
        return (plqueue ->f ->data);
}
int main()
{
    PLinkQueue lqueue = createEmptyQueue();
    cout<<"创建一个n元素的队列\n输入n"<<endl;
    int n,t;
    cin>>n;
    t = n;
    while(n)
    {
        int data;
        cin>>data;
        enQueue(lqueue,data);
        n--;
    }
    cout<<"取队头并出队"<<endl;
    while(t)
    {
        cout<<getFront(lqueue)<<" ";
        deQueue(lqueue);
        t--;
    }
    cout<<endl;
    return 0;
}
