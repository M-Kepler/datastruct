/***********************************************************
* Author       : M_Kepler
* EMail        : hellohuangjinjie@gmail.com
* Last modified: 2016-04-15 21:08:37
* Filename     : tree-pro.cpp
* Description  :
   层数(深度)高度:从0开始（2^0)
   七大性质：
   非空二叉树第i层结点最多为2^i 个结点
   高度为 K 的二叉树中，最多有 2^(k+1) - 1 个结点
   n0 = n2 + 1

   完全二叉树：
   叶子只出现在最后两层，最后一层结点都分布在左边
   深度：log2(n) n 为结点数

   满二叉树：
   度数只可能是 n0、n2
   深度为 k 的完全二叉树去掉第K层就变为满二叉树了

   扩充二叉树：
   添加外层结点，把原树中的结点的度数都补为2
   外部结点个数 N 内部结点个数 n     N - n = 1
   外部路径 E 内部路径 I             E - I = 2n

   度数 + 1 = 结点数

**********************************************************/

#include <iostream>
#include <malloc.h>
#include <math.h>
#include <stack>
#include <queue>
#define abs(x)(x>0?x:(-x))
#define maxsize 100
using namespace std;

//二叉树结点
typedef int DateType;
typedef struct BiTNode{
    DateType data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

//按先序序列创建二叉树
int CreateBiTree(BiTree &T){
    char data;
    //‘#’表示空树
    cin>>data;
    if(data == '#'){
        T = NULL;
    }
    else{
        T = (BiTree)malloc(sizeof(BiTNode));
        T->data = data;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
    return 0;
}


//层次创建二叉树
BiTree createBiTree()
{
    char ch;
    BiTNode*Q[maxsize];
    int front,rear;
    BiTree root, s;
    root=NULL;
    front=1;rear=0;
    printf("按层次输入二叉树，虚结点输入'.'，以'#'结束输入：\n");
    while((ch=getchar())!='#')
    {
        s=NULL;
        if(ch!='.')
        {
            s=(BiTree)malloc(sizeof(BiTree));
            s->data=ch;
            s->lchild=NULL;
            s->rchild=NULL;
        }
        rear++;
        Q[rear]=s;
        if(rear==1)root=s;
        else
        {
            if(s&&Q[front])
                if(rear%2==0)Q[front]->lchild=s;
                else Q[front]->rchild=s;
            if(rear%2==1)front++;
        }
    }
    return root;
}

//访问结点
void Visit(BiTree T){
    if(T->data != '#'){
        printf("%c ",T->data);
    }
}

//先序遍历
void PreOrder(BiTree T){
    if(T != NULL){
        //访问根节点
        Visit(T);
        //访问左子结点
        PreOrder(T->lchild);
        //访问右子结点
        PreOrder(T->rchild);
    }
}
//中序遍历
void InOrder(BiTree T){
    if(T != NULL){
        //访问左子结点
        InOrder(T->lchild);
        //访问根节点
        Visit(T);
        //访问右子结点
        InOrder(T->rchild);
    }
}
//后序遍历
void PostOrder(BiTree T){
    if(T != NULL){
        //访问左子结点
        PostOrder(T->lchild);
        //访问右子结点
        PostOrder(T->rchild);
        //访问根节点
        Visit(T);
    }
}


//树的高度
int BinTreeDepth(BiTree t)
{
    //Depth(t)= max( Depth(lchild),Depth(rchild) ) + 1
    int h,h1,h2;
    if(t == NULL)   return 0;
    else
    {
        h1 = BinTreeDepth(t->lchild);
        h2 = BinTreeDepth(t->rchild);
        h = max(h1,h2) + 1;
        return h;
    }

}


//求树的结点数
int getNodeNum(BiTree t)
{
    //树的结点数=左子树 + 右子树 + 1；
    if(t == NULL) return 0;
    return (getNodeNum(t->lchild)+getNodeNum(t->rchild)+1);
}


//求二叉树第K层的节点个数
int GetNodeNumKthLevel(BiTree t, int k)
{
    //NodeNum(t,k) = NodeNum(t->lchild,k-1)+NodeNum(t->rchild,k-1)
    if(t == NULL || k < 1)
        return 0;
    if(k == 1)
        return 1;
    // 左子树中k-1层的节点个数
    int numLeft = GetNodeNumKthLevel(t->lchild, k-1);
    // 右子树中k-1层的节点个数
    int numRight = GetNodeNumKthLevel(t->rchild, k-1);
    return (numLeft + numRight);
}


//求二叉树中叶子节点的个数
int GetLeafNodeNum(BiTree t)
{
    //左右儿子为NULL    则：LeafNum(t) = LeafNum(t->lchild) + LeafNum(t->rchild);
    if(t == NULL)
        return 0;
    if(t->lchild ==NULL && t->rchild ==NULL)
        return 1;
    int numleft = GetLeafNodeNum(t->lchild);
    int numright = GetLeafNodeNum(t->rchild);
    return (numleft + numright);
}


//求二叉树中节点的最大距离
int GetMaxDistance(BiTree t, int & maxLeft, int & maxRight)
{
    //MaxDistance(t->lchild)    //MacDistance(t->rchild)    //MaxLeft(t->lchild)+MaxRight(t->rchild)
    // maxLeft,maxRight 左/右 子树中的节点距离根节点的最远距离
    if(t == NULL)
    {
        maxLeft = 0;
        maxRight = 0;
        return 0;
    }
    int maxLL, maxLR, maxRL, maxRR;
    int maxDistLeft, maxDistRight;
    if(t->lchild != NULL)
    {
        maxDistLeft = GetMaxDistance(t->lchild, maxLL, maxLR);
        maxLeft = max(maxLL, maxLR) + 1;
    }
    else
    {
        maxDistLeft = 0;
        maxLeft = 0;
    }
    if(t->rchild != NULL)
    {
        maxDistRight = GetMaxDistance(t->rchild, maxRL, maxRR);
        maxRight = max(maxRL, maxRR) + 1;
    }
    else
    {
        maxDistRight = 0;
        maxRight = 0;
    }
    return max(max(maxDistLeft, maxDistRight), maxLeft+maxRight);
}


//两结点最低公共祖先
DateType GetLastCommonParent(BiTree t, DateType x, DateType y)
{

}
//如果两个节点分别在根节点的左子树和右子树，则返回根节点
//如果两个节点都在左子树，则递归处理左子树；如果两个节点都在右子树，则递归处理右子树
//求最近公共祖先：


//判断二叉树是不是平衡二叉树
bool isAVL(BiTree t, int & height)
{
    //如果左子树和右子树都是AVL树并且左子树和右子树高度相差不大于1，返回真，其他返回假
    if(t == NULL) // 空树，返回真
    {
        height = 0;
        return true;
    }
    int heightLeft;
    bool resultLeft = isAVL(t->lchild, heightLeft);
    int heightRight;
    bool resultRight = isAVL(t->rchild, heightRight);
    // 左子树和右子树都是AVL，并且高度相差不大于1，返回真
    if(resultLeft && resultRight && abs(heightLeft - heightRight) <= 1)
    {
        height = max(heightLeft, heightRight) + 1;
        return true;
    }
    else
    {
        height = max(heightLeft, heightRight) + 1;
        return false;
    }
}


//释放树空间
void DestroyBinTree(BiTree t)
{
    if(t == NULL) return;
    DestroyBinTree( t->lchild );
    DestroyBinTree( t->rchild );
    t->lchild = NULL;
    t->rchild = NULL;
    free( t );
}


//先序遍历(非递归)
void PreOrder2(BiTree T){
    //思路：访问T->data后，将T入栈，遍历左子树；遍历完左子树返回时，栈顶元素应为T，出栈，再先序遍历T的右子树。
    stack<BiTree> stack;
    //p是遍历指针
    BiTree p = T;
    //栈不空或者p不空时循环
    while(p || !stack.empty()){
        if(p != NULL){
            //存入栈中
            stack.push(p);
            //访问根节点
            printf("%c ",p->data);
            //遍历左子树
            p = p->lchild;
        }
        else{
            //退栈
            p = stack.top();
            stack.pop();
            //访问右子树
            p = p->rchild;
        }
    }//while
}
//中序遍历(非递归)
void InOrder2(BiTree T)
{
    //思路：T是要遍历树的根指针，中序遍历要求在遍历完左子树后，访问根，再遍历右子树。先将T入栈，遍历左子树；
    //遍历完左子树返回时，栈顶元素应为T，出栈，访问T->data，再中序遍历T的右子树。

    stack<BiTree> stack;
    //p是遍历指针
    BiTree p = T;
    //栈不空或者p不空时循环
    while(p || !stack.empty()){
        if(p != NULL){
            //存入栈中
            stack.push(p);
            //遍历左子树
            p = p->lchild;
        }
        else{
            //退栈，访问根节点
            p = stack.top();
            printf("%c ",p->data);
            stack.pop();
            //访问右子树
            p = p->rchild;
        }
    }//while
}
//后序遍历(非递归)
typedef struct BiTNodePost{
    BiTree biTree;
    char tag;
}BiTNodePost,*BiTreePost;
//后序遍历
void PostOrder2(BiTree T){
    stack<BiTreePost> stack;
    //p是遍历指针
    BiTree p = T;
    BiTreePost BT;
    //栈不空或者p不空时循环
    while(p != NULL || !stack.empty()){
        //遍历左子树
        while(p != NULL){
            BT = (BiTreePost)malloc(sizeof(BiTNodePost));
            BT->biTree = p;
            //访问过左子树
            BT->tag = 'L';
            stack.push(BT);
            p = p->lchild;
        }
        //左右子树访问完毕访问根节点
        while(!stack.empty() && (stack.top())->tag == 'R'){
            BT = stack.top();
            //退栈
            stack.pop();
            BT->biTree;
            printf("%c ",BT->biTree->data);
        }
        //遍历右子树
        if(!stack.empty()){
            BT = stack.top();
            //访问过右子树
            BT->tag = 'R';
            p = BT->biTree;
            p = p->rchild;
        }
    }//while
}


//层次遍历
void LevelOrder(BiTree T){
    BiTree p = T;
    //队列
    queue<BiTree> queue;
    //根节点入队
    queue.push(p);
    //队列不空循环
    while(!queue.empty()){
        //对头元素出队
        p = queue.front();
        //访问p指向的结点
        printf("%c ",p->data);
        //退出队列
        queue.pop();
        //左子树不空，将左子树入队
        if(p->lchild != NULL){
            queue.push(p->lchild);
        }
        //右子树不空，将右子树入队
        if(p->rchild != NULL){
            queue.push(p->rchild);
        }
    }
}


int main()
{

    //测试：ABC##DE#G##F###     124##57##8##3#6##       

    BiTree T;
    cout<<"请输入二叉树创建方式     1：先序，2：层次"<<endl;
    int a;  cin>>a;
    switch(a){
        case(1):
            cout<<"先序输入二叉树"<<endl;
            CreateBiTree(T);
            break;
        case(2):
            T = createBiTree( );    //Test case: ebfad.g..c#
            break;
    }
    printf("先序遍历：\n");
    PreOrder(T);
    printf("\n");

    printf("先序遍历(非递归)：\n");
    PreOrder2(T);
    printf("\n");

    printf("中序遍历：\n");
    InOrder(T);
    printf("\n");

    printf("中序遍历(非递归)：\n");
    InOrder2(T);
    printf("\n");

    printf("后序遍历：\n");
    PostOrder(T);
    printf("\n");

    printf("后序遍历(非递归)：\n");
    PostOrder2(T);
    printf("\n");

    printf("层次遍历：\n");
    LevelOrder(T);
    printf("\n");

    cout<<endl<<"树的高度为："<<BinTreeDepth(T)<<endl<<endl;

    cout<<"结点数"<<getNodeNum(T)<<endl<<endl;

    cout<<"求二叉树第K层的节点个数"<<endl;
    int k;  cin>>k;
    cout<<"个数为"<<endl<<GetNodeNumKthLevel(T,k)<<endl<<endl;

    cout<<"二叉树中叶子节点的个数\n";
    cout<<endl<<GetLeafNodeNum(T)<<endl<<endl;

    int maxLeft = 0;
    int maxRight = 0;
    cout<<"二叉树中节点的最大距离\n";
    cout<<GetMaxDistance(T, maxLeft, maxRight)<<endl<<endl;

    cout<<"两结点最低公共祖先\n";
    DateType A,B;
    cin>>A>>B;
    cout<<GetLastCommonParent(T,A,B)<<endl;

    int height = 0;
    cout<<"判断二叉树是不是平衡二叉树\n"<<isAVL(T,height)<<endl<<endl;

    cout <<"释放树空间"<<endl<<endl;
    DestroyBinTree(T);

    return 0;
}

/* Sample input
 * A B D C E G F H I
 * A B D # # # C E # G # # F H # # I # #
 */
