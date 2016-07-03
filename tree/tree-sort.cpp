#include <iostream>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

typedef int DataType;
struct BinSearchNode;
typedef struct BinSearchNode *PBinSearchNode;
struct BinSearchNode {
    DataType info;
    struct BinSearchNode *llink, *rlink;
    // PBinSearchNode llink,rlink;
};
typedef struct BinSearchNode *BinSearchTree;
typedef BinSearchTree *PBinSearchTree;

int searchNode(PBinSearchTree ptree,DataType info,PBinSearchNode *position) {
    PBinSearchNode p,q;
    p = *ptree;
    q = p;
    while(p!=NULL) {
        q=p;
        if(p->info == info) {
            *position = p; return 1;
        }
        else if(p->info > info)
            p = p->llink;
        else
            p= p->rlink;
    }
    *position = q;
    return 0;
}

bool searchNode(PBinSearchTree root, DataType key) {
    PBinSearchNode currentNode;
    currentNode = *root;
    bool found;
    while(currentNode != NULL) {
        if (currentNode->info == key)
            found = true;
        else if (currentNode->info < key)
            currentNode = currentNode->rlink;
        else
            currentNode = currentNode->llink;
   }
}

//insert

int insertSearchTree(PBinSearchTree ptree,DataType info) {
    PBinSearchNode p,position;
    if(searchNode(ptree,info,&position) == 1)
        return 1;
    p = (PBinSearchNode) malloc (sizeof(struct BinSearchNode));

    if(p==NULL)
    {
        printf("Error\n");
        return 0;
    }
    p->info = info;
    p->llink = p->rlink = NULL;
    if(position == NULL)
        *ptree = p;
    else if(info < position->info)
        position->llink = p;
    else
        position->rlink = p;
    return 1;
}

void insertNode(PBinSearchTree root, DataType key) {
    PBinSearchNode p,q,fatherNode;
    q->info = key;
    q->llink = q->rlink = NULL;
    p = *root;
    if(p == NULL)
        q = p;
    while(p != NULL) {
        fatherNode = p;
        if (p->info == key)
            printf("Error\n");
        else if(p->info < key)
            p = p->rlink;
        else
            p = p->llink;
    }
    if(fatherNode->info < key)
        fatherNode->rlink = q;
    else
        fatherNode->llink = q;
}

//构造
struct DicElement {
    DataType value;
};

struct SeqDictionary {
    int n;
    DicElement *element;
};

int createSearchTree(PBinSearchTree ptree,SeqDictionary *dic) {
    int i;
    *ptree = NULL;
    for(i = 0;i<dic->n;i++)
        //if(!insertSearchTree(ptree,dic->element[i].info))
        if(!insertSearchTree(ptree,dic->element[i].value))
            return 0;
    return 1;
}

//delete
int deleteSearchTree(PBinSearchTree ptree,DataType info) {
    PBinSearchNode parentp,p,r;
    p = *ptree;
    parentp = NULL;
    if(p == NULL)
        return 0;
    while(p != NULL) {
        if(p->info == info)
            break;
        parentp = p;
        if(p->info > info)
            p = p->llink;
        else
            p = p->rlink;
    }
    if(p->llink == NULL)    //被删结点 P 无左子树
    {
        //被删除的结点是根结点
        if(parentp == NULL)
            *ptree = p->rlink;

        else if(parentp->llink == p)
            parentp ->llink = p->rlink;
        else
            parentp ->rlink = p->rlink;
    }

}

void createTree(PBinSearchTree root) {
    DataType a[10]={12,44,52,88,18,9,13,82,41,51};
    for (int i=0;i<10;i++)
    {
        insertSearchTree(root, a[i]);
    }
}

void Visit(BinSearchTree T)
{
    printf("%d ", T->info);
}
void InOrder(BinSearchTree root) {
    if(root!= NULL) {
        InOrder(root->llink);
        Visit(root);
        InOrder(root->rlink);
    }
}

int main()
{
    BinSearchTree T;
    PBinSearchTree p;
    T=*p;
    DataType data;
    createTree(p);
    InOrder(T);
    return 0;
}
