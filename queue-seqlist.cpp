#include <iostream>
#include <malloc.h>
#define MAXNUM 9999
using namespace std;
typedef int DataType;
struct SeqQueue
{
    int f,r;
    DataType s[MAXNUM];
};
typedef struct SeqQueue* PSeqQueue;

PSeqQueue createEmptyQueue()
{
    PSeqQueue paqu = (PSeqQueue) malloc (sizeof(struct SeqQueue));
    if( paqu != NULL)
        paqu ->f = paqu->r = 0;
    else
        printf("Out of Space\n");
    return paqu;
}

void enQueue_seq(PSeqQueue paqu, DataType x)
{
    if( (paqu->r+1) % MAXNUM == paqu->f)
        printf("Full queue.\n");
    else
    {
        paqu->s[paqu->r] = x;
        //是考虑到了到环形队列的假溢出
        paqu->r = (paqu->r+1) % MAXNUM;
    }
}

void deQueue_seq(PSeqQueue paqu)
{
    if(paqu->f == paqu->r)
        printf("Empty Queue\n");
    else
        paqu->f = (paqu->f+1) % MAXNUM;
}

DataType forntQueue_seq(PSeqQueue paqu)
{
    if(paqu->f == paqu->r)
        printf("Empty Queue\n");
    else
        return (paqu->s[paqu->f]);
}

int main()
{
    PSeqQueue paqu = createEmptyQueue();
    cout<<"创建一个n元素的队列\n输入n"<<endl;
    int n,t;
    cin>>n;
    t = n;
    while(n)
    {
        int data;
        cin>>data;
        enQueue_seq(paqu,data);
        n--;
    }
    cout<<"取队头并出队"<<endl;
    while(t)
    {
        cout<<forntQueue_seq(paqu)<<" ";
        deQueue_seq(paqu);
        t--;
    }
    cout<<endl;
    return 0;
}
