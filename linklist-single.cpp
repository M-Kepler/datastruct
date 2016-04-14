/***********************************************************
* Author       : M_Kepler
* EMail        : hellohuangjinjie@gmail.com
* Last modified: 2016-04-14 12:02:04
* Filename     : linklist-single.cpp
* Description  : 带头结点的单链表
    *由于我使用0表示输入结束，所以尽量不要插入0
***********************************************************/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

using namespace std;
typedef int DataType;
struct Node;
typedef struct Node * PNode;

struct Node{
    DataType info;
    PNode link;
};
typedef struct Node * LinkList;

//创建空链表
LinkList createNullList_link()
{
    LinkList llist = (LinkList)malloc (sizeof(struct Node));
    if (llist != NULL)
        llist->link = NULL;
    else
        printf("Out of space !\n");
    return llist;
}

//判断链表是否为空
int isNullList_link (LinkList llist){
    return (llist -> link == NULL);
}

void showLinkList(LinkList llist)
{
    PNode tmp = llist;
    while(tmp!=NULL & tmp->link != NULL)
    {
        tmp = tmp->link;
        cout<<tmp->info<<" ";
    }
    cout<<endl;
}
//求某元素的储存位置
PNode locate_x(LinkList llist,DataType x){
    PNode p;
    if ( llist == NULL ) return NULL;
    p = llist -> link;
    while ( p!=NULL && p->info != x)
        p = p->link; //指针循环移动
    return p;
}

//单链表的插入
int insertPost_link (LinkList llist,PNode p,DataType x)
{
    PNode q = (PNode) malloc (sizeof(struct Node));
    if (q==NULL){
        printf("Out of space\n");
        return 0;
    }
    else{
        q ->info =x;
        q ->link =p->link; //先右
        p->link =q;  //后左
        return 1;
    }
}

//在单链表中求p所指结点的前驱结点：
PNode locatePre_link(LinkList llist,PNode p){
    PNode p1;
    if(llist ==NULL)
        return NULL;
    p1=llist;
    while( p1 != NULL && p1 ->link != p)//p1->link指向的就是p
        p1 = p1->link;
    return p1;
}

//单链表的删除
int deleteV_link(LinkList llist,DataType x){
    PNode p,q;
    p =llist;
    if( p==NULL )
        return 0;
    //寻找x所在的结点
    while(p->link != NULL && p->link->info != x)
        p=p->link;

    if(p->link==NULL){
        printf("Not exist!\n");
        return 0;
    }
    else{
        q = p->link;  //定q结点为x所在结点
        p->link = q->link ;
        free(q);
        return 1;
    }
}

//删除下标为i的结点
int deleteP_link(LinkList llist, int i){
    PNode p;
    p=llist;

    for(int j=0;j<i;j++){
        if(!p->link){
            printf("Not exist\n");
            return 0;
        }
        else
            p=p->link;
    }
    p->link=p->link->link;
}

/*
 * 值得思考的问题
 * 1. 将1结点后的2～n结点一个个插入到head结点后,
 * h 1 2 3 4 5 6
     * h 1 2 3 4 5 6
     * h 2 1 3 4 5 6
     * h 3 2 1 4 5 6
     * h 4 3 2 1 5 6
     * h 5 4 3 2 1 6
     * h 6 5 4 3 2 1
 */
LinkList reverLinkList(LinkList llist)
{
    PNode tmp;
    tmp = llist->link;//1
    PNode q;
    while(tmp->link!= NULL){
        q = tmp->link;//2
        tmp->link = q->link; //先把3和1接起
        q->link = llist->link; //把2和1接起
        llist->link = q;//把h和2接起
    }
    /*纠结着第6个结点
     *其实while循环处理的是tmp->link,而不是tmp
     *所以6是可以正常插入的
     */

    return llist;

}

int main()
{
    LinkList llist = createNullList_link();
    PNode head=llist;
    PNode tmp;
    DataType data;
    cin>>data;
    while(data)
    {
        insertPost_link(llist, head, data);
        cin>>data;
    }

    cout<<"由于是前插，所以实际顺序与输入顺序相反\n";
    showLinkList(llist);

    if(!isNullList_link(llist))
        cout<<"linklist is not empty\n";
/*
    DataType key;
    cout<<"locate_key:\n";
    cin>>key;
    tmp = locate_x(llist, key);
    cout<<tmp->info<<endl;

    cout<<"insert data1 after_data2:\n";
    DataType data1,data2;
    cin>>data1>>data2;
    tmp = locate_x(llist,data1);
    insertPost_link(llist, tmp, data2);
    showLinkList(llist);

    cout<<"locatePre_link,cin current data\n";
    cin>>data;
    tmp = locate_x(llist,data);
    PNode tmp2;
    tmp2 = locatePre_link(llist, tmp);
    cout<<tmp2->info<<endl;

    cout<<"deleteV_link,cin data\n";
    cin>>data;
    deleteV_link(llist, data);
    showLinkList(llist);

    cout<<"delete locate i,cin i\n";
    cin>>data;
    deleteP_link(llist,data);
    showLinkList(llist);
*/
    cout<<"reversal LinkList\n";
    LinkList tmp_link = reverLinkList(llist);
    showLinkList(tmp_link);
    return 0;
}
