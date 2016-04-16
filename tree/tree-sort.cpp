#include <iostream>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
typedef int DataType;
struct BinSearchNode;
typedef struct BinSearchNode *PBinSearchNode;
struct BinSearchNode
{
    DataType key;
    PBinSearchNode llink,rlink;
};
typedef struct BinSearchNode *BinSearchTree;
typedef BinSearchTree *PBinSearchTree;

//二叉树的检索
int search(PBinSearchTree ptree,DataType key,PBinSearchNode *position)
{
    PBinSearchNode p,q;
    p = *ptree;
    q = p;
    while(p!=NULL)
    {
        q=p;
        if(p->key == key){ *position = p; return 1; }
        else if(p->key > key) p = p->llink;
        else
            p= p->rlink;
    }
    *position = q;
    return 0;
}

//插入
int insertSearchTree(PBinSearchTree ptree,DataType key)
{
    PBinSearchNode p,position;
    if(search(ptree,key,&position) == 1)
        return 1;
    p = (PBinSearchNode) malloc (sizeof(struct BinSearchNode));

    if(p==NULL)
    {
        printf("Error\n");
        return 0;
    }
    p->key = key;
    p->llink = p->rlink = NULL;
    if(position == NULL)
        *ptree = p;
    else if(key < position->key)
        position->llink = p;
    else
        position->rlink = p;
    return 1;
}

//构造
struct DicElement
{
    DataType value;
};

struct SeqDictionary
{
    int n;
    DicElement *element;
};

int createSearchTree(PBinSearchTree ptree,SeqDictionary *dic)
{
    int i;
    *ptree = NULL;
    for(i = 0;i<dic->n;i++)
        //if(!insertSearchTree(ptree,dic->element[i].key))
        if(!insertSearchTree(ptree,dic->element[i].value))
            return 0;
    return 1;
}

//删除
int deleteSearchTree(PBinSearchTree ptree,DataType key)
{
    PBinSearchNode parentp,p,r;
    p = *ptree;
    parentp = NULL;
    while(p != NULL)
    {
        if(p->key == key)
            break;
        parentp = p;
        if(p->key > key)
            p = p->llink;
        else
            p = p->rlink;
    }
    if(p == NULL)
        return 0;

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
int main()
{
    cout<<"create tree\n";
    return 0;
}
