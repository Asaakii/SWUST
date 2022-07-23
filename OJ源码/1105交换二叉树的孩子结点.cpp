#include <bits/stdc++.h>

using namespace std;

#define CRL(a) memset(a,0,sizeof(a))
#define NewNode (TreeNode*) malloc (sizeof(TreeNode))

typedef struct node
{
	char data;
	node *Lchild,*Rchild;
} TreeNode;

TreeNode * Built()
{
	TreeNode *T;
	char ch;
	cin >> ch;
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

void Change(TreeNode *&Tem)
{
	if (Tem==NULL)
		return;
	swap(Tem->Lchild,Tem->Rchild);
	Change(Tem->Lchild);
	Change(Tem->Rchild);
}

void Put1(TreeNode *&Tem)
{
	if (Tem==NULL)
		return;
	Put1(Tem->Lchild);
	cout << Tem->data;
	Put1(Tem->Rchild);
}

void Put2(TreeNode *&Tem)
{
	if (Tem==NULL)
		return;
	cout << Tem->data;
	Put2(Tem->Lchild);
	Put2(Tem->Rchild);
}

int main()
{
	TreeNode *Root;
	Root=Built();
	Change(Root);
	Put1(Root);cout << endl;
	Put2(Root);
	return 0;
}
