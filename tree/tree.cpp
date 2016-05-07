/***********************************************************
* Author       : M_Kepler
* EMail        : hellohuangjinjie@gmail.com
* Last modified: 2016-05-05 16:17:02
* Filename     : tree.cpp
* Description  :
    * ./tree.md
    * 需要了解在二叉树里怎么使用递归,只要把树根栽进入就行，注意在程序
        * 里要有跳出递归的语句,一般都是Tree不空就递归
    * 创建结点:
        * 采用的是链式存储，所以结点就是一个两个指针的链表结点
**********************************************************/

#include <iostream>
#include <malloc.h>
#include <math.h>
#include <stack>
#include <queue>
#define abs(x)(x>0?x:(-x))
#define maxsize 100
using namespace std;

typedef char DateType;
//二叉树结点(链式存储)
typedef struct BiTNode{
    DateType data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

//按先序序列创建二叉树
int CreateBiTree(BiTree &T){
    DateType data;
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
/*
 * 1.根据结点的序号关系，在数组中，父结点为i，左儿子为2×i，右儿子为2×i+1
     * 定义两个哨兵front、rear分别指向父结点和子结点
     * 判断如果输入的不是虚结点就初始化一个结点
     * 把输入的结点放到Q[rear]里,并判断是不是第一个结点<根结点>
     * 判断是否分到结点空间，如果没有分到就是虚结点啊
     * 根据rear的值来确定是左还是右儿子
 * 2.利用queue,
 */

BiTree createBiTree() {
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
        //安置结点
        if(ch!='.')
        {
            s=(BiTree)malloc(sizeof(BiTree));
            s->data=ch;
            s->lchild=NULL;
            s->rchild=NULL;
        }
        rear++;
        Q[rear]=s;
        //根结点
        if(rear==1)
            root=s;
        else
        {
            if(s && Q[front])
                if(rear%2==0)
                    Q[front]->lchild=s;
                else
                    Q[front]->rchild=s;
            if(rear%2==1)
                front++;
        }
    }
    return root;
}

//访问结点
void Visit(BiTree T) {
    if(T->data != '#'){
        printf("%c ",T->data);
    }
}

//先序遍历
void PreOrder(BiTree T){
    if(T != NULL){
        Visit(T);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

//中序遍历
void InOrder(BiTree T){
    if(T != NULL){
        InOrder(T->lchild);
        Visit(T);
        InOrder(T->rchild);
    }
}

//后序遍历
void PostOrder(BiTree T){
    if(T != NULL){
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        Visit(T);
    }
}

//树的高度
//Depth(t)= max( Depth(lchild),Depth(rchild) ) + 1
int BinTreeDepth(BiTree t) {
    int h,h1,h2;
    if(t == NULL)
        return 0;
    else
    {
        h1 = BinTreeDepth(t->lchild);
        h2 = BinTreeDepth(t->rchild);
        // 当递归到最后一个结点，h1h2都为0,所以，只要有一个结点高度都为１
        h = max(h1,h2) + 1;
        return h;
    }
}

//求树的结点数
//NodeNum=左子树 + 右子树 + 1；
int getNodeNum(BiTree t) {
    if(t == NULL)
        return 0;
    return (getNodeNum(t->lchild)+getNodeNum(t->rchild)+1);
}

//求二叉树第K层的节点个数
//NodeNum(t,k) = NodeNum(t->lchild,k-1)+NodeNum(t->rchild,k-1)
int GetNodeNumKthLevel(BiTree t, int k) {
    if(t == NULL || k < 1)
        return 0;
    if(k == 1)
        return 1;
    int numLeft = GetNodeNumKthLevel(t->lchild, k-1);
    int numRight = GetNodeNumKthLevel(t->rchild, k-1);
    return (numLeft + numRight);
}

//求二叉树中叶子节点的个数
//左右儿子为NULL 则：LeafNum(t) = LeafNum(t->lchild) + LeafNum(t->rchild);
int GetLeafNodeNum(BiTree t) {
    if(t == NULL)
        return 0;
    if(t->lchild ==NULL && t->rchild ==NULL)
        return 1;
    int numleft = GetLeafNodeNum(t->lchild);
    int numright = GetLeafNodeNum(t->rchild);
    return (numleft + numright);
}

//输出叶子结点
// if(t->lchild==NULL && t->rchild==NULL)
void displayLeaf(BiTree t) {
    if(t!=NULL) {
        if(t->lchild==NULL && t->rchild==NULL) {
            cout<<t->data<<" ";
        }
        else{
            displayLeaf(t->lchild);
            displayLeaf(t->rchild);
        }
    }
}

// *求二叉树中节点的最大距离
int GetMaxDistance(BiTree t, int & maxLeft, int & maxRight) {
    //MaxDistance(t->lchild)
    //MacDistance(t->rchild)
    //MaxLeft(t->lchild)+MaxRight(t->rchild)
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
    } else {
        maxDistLeft = 0;
        maxLeft = 0;
    }

    if(t->rchild != NULL)
    {
        maxDistRight = GetMaxDistance(t->rchild, maxRL, maxRR);
        maxRight = max(maxRL, maxRR) + 1;
    } else {
        maxDistRight = 0;
        maxRight = 0;
    }

    return max(max(maxDistLeft, maxDistRight), maxLeft+maxRight);
}

// *两结点最低公共祖先
DateType GetLastCommonParent(BiTree t, DateType x, DateType y) {
    //如果两个节点分别在根节点的左子树和右子树，则返回根节点
    //如果两个节点都在左子树，则递归处理左子树；如果两个节点都在右子树，则递归处理右子树
}

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

    BiTree T;
    cout<<"请输入二叉树创建方式     1：先序，2：层次"<<endl;
    cout<<"先序:A B D # # # C E # G # # F H # # I # #\n";
    cout<<"层次:ebfad.g..c#\n";
    int a; cin>>a;
    switch(a){
        case(1):
            cout<<"先序输入二叉树"<<endl;
            CreateBiTree(T);
            break;
        case(2):
            //Test case: ebfad.g..c#
            T = createBiTree( );
            break;
    }
    printf("1. 先序遍历：\n");
    PreOrder(T);
    printf("\n");

    printf("2. 先序遍历(非递归)：\n");
    PreOrder2(T);
    printf("\n");

    printf("3. 中序遍历：\n");
    InOrder(T);
    printf("\n");

    printf("4. 中序遍历(非递归)：\n");
    InOrder2(T);
    printf("\n");

    printf("5. 后序遍历：\n");
    PostOrder(T);
    printf("\n");

    printf("6. 后序遍历(非递归)：\n");
    PostOrder2(T);
    printf("\n");

    printf("7. 层次遍历：\n");
    LevelOrder(T);
    printf("\n");

    cout<<endl<<"8. 树的高/深度为："<<BinTreeDepth(T)<<endl<<endl;

    cout<<"结点数"<<getNodeNum(T)<<endl<<endl;

    cout<<"9. 求二叉树第K层的节点个数"<<endl;
    int k;
    cin>>k;
    cout<<"个数为"<<endl<<GetNodeNumKthLevel(T,k)<<endl<<endl;

    cout<<"10. 二叉树中叶子节点的个数\n";
    cout<<endl<<GetLeafNodeNum(T)<<endl<<endl;

    cout<<"11. 输出二叉树中叶子节点\n";
    displayLeaf(T);
    cout<<endl;

    int maxLeft = 0;
    int maxRight = 0;
    cout<<"12. 二叉树中节点的最大距离\n";
    cout<<GetMaxDistance(T, maxLeft, maxRight)<<endl<<endl;

    cout<<"13. 两结点最低公共祖先\n";
    DateType A,B;
    // cin>>A>>B;
    cout<<GetLastCommonParent(T,A,B)<<endl;

    int height = 0;
    cout<<"14. 判断二叉树是不是平衡二叉树\n"<<isAVL(T,height)<<endl<<endl;

    cout <<"释放树空间"<<endl<<endl;
    DestroyBinTree(T);

    return 0;
}

/* Sample input
 //测试：ABC##DE#G##F###     124##57##8##3#6##
 * A B D C E G F H I
 * A B D # # # C E # G # # F H # # I # #
 */
