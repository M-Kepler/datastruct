#include <iostream>
#include <malloc.h>
using namespace std;
const int MAXNUM = 9999;
typedef int DataType;
struct SeqStack
{
    int t;      //指向栈顶的位置，而不是元素个数
    DataType s[MAXNUM];
};
typedef struct SeqStack* PSeqStack;

PSeqStack  createEmptyStack_seq( ) {
    PSeqStack pastack = (PSeqStack)malloc(sizeof(struct SeqStack));
    if (pastack==NULL)
        printf("Out of space!! \n");
    else
        pastack->t = -1;
    return pastack;
}

int  isEmptyStack_seq( PSeqStack pastack ) {
    return pastack->t == -1;
}

void  push_seq( PSeqStack pastack, DataType x ) {
    if( pastack->t >= MAXNUM - 1  )
        printf( "Overflow! \n" );
    else
    {
        pastack->t = pastack->t+1;
        pastack->s[pastack->t] = x;
    }
}

void  pop_seq( PSeqStack pastack ) {
    if (pastack->t == -1 )
        printf( "Underflow!\n" );
    else
        pastack->t = pastack->t-1;
}

DataType top_seq( PSeqStack pastack ) {
    if(pastack ->t == -1)
        printf("It is empty!\n");
    return (pastack->s[pastack->t]);
}

void showStack_seq(PSeqStack pastack)
{
    while(pastack->t != -1)
    {
        cout<<top_seq(pastack)<<" ";
        pop_seq(pastack);
    }
}

int main()
{
    int n,t;
    DataType item;
    cout<<"please input stack length:\n";
    cin>>n;
    t=n;
    PSeqStack pastack = createEmptyStack_seq();
    while(n)
    {
        cin>>item;
        push_seq(pastack,item);
        n--;
    }
    showStack_seq(pastack);

    return 0;
}
