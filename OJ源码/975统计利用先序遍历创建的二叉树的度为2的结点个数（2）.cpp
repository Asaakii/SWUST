#include<iostream>
#include<malloc.h>
using namespace std;
#define CRL(a) memset(a,0,sizeof(a))
#define NewNode (TreeNode *) malloc (sizeof(TreeNode))
#define MAX 0xfffffff
typedef unsigned long long LL;
typedef  long long ll;
const int mod =1e9+7;

typedef struct node {
    char data;
    node *Lchild,*Rchild;
} TreeNode;

TreeNode *Built() {
    TreeNode *T;
    char ch;
    cin>>ch;
    if(ch=='#')
        T=NULL;
    else {
        T=NewNode;
        T->data=ch;
        T->Lchild=Built();
        T->Rchild=Built();
    }
    return T;
}

int Count(TreeNode *&Tem) {
    if(Tem==NULL) return 0;
    if((Tem->Lchild!=NULL)&&(Tem->Rchild!=NULL))    //如果当前节点的左右儿子都不为空，说明他度数为2，ans++
        return 1+Count(Tem->Lchild)+Count(Tem->Rchild); //1就是ans+1
    return (Count(Tem->Lchild)+Count(Tem->Rchild)); //否则就不+1

}

int main() {
    TreeNode *Root;
    Root=Built();
    cout<<Count(Root);
    return 0;
}
