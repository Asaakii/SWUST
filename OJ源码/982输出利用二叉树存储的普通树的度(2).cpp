#include <bits/stdc++.h>

#define NewNode (node*)malloc(sizeof(node))

using namespace std;

int ans=0;

struct node
{
	char data;
	node *Lchild;
	node *Rchild;
};

node * Built()
{
	node *T;
	char ch=getchar();
	if (ch=='#')
		T=NULL;
	else
	{
		T=NewNode;
		T->data=ch;
		T->Lchild=Built();
		T->Rchild=Built();
	}
	return T;
}

//二叉树储存数的时候，每个节点的左儿子依旧表示儿子，而右儿子则变成了兄弟节点

int Count(node *&T)
{
	if (T==NULL)
		return 0;   //如果这个节点不存在，返回0 
	ans=max(ans,Count(T->Lchild));//否则，查看儿子节点中度数最大的，和当前的ans做比较 
	ans=max(ans,Count(T->Rchild)+1);//查看当前节点有几个兄弟，兄覅数+1（自己）就是父节点的度数，和ans作比较 
	return ans;
}

int main()
{
	node *root=Built();
	if (root->Rchild!=NULL)//如果根节点有兄弟，则说明不止一棵树 
		cout << "ERROR";
	else
		cout << Count(root);
	return 0;
}
