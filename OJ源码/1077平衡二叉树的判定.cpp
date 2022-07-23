#include <bits/stdc++.h>

using namespace std;

int Flag=0;
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
		T=new node;
		T->data=ch;
		T->Lchild=Built();
		T->Rchild=Built();
	}
	return T;
}

int Deep(TreeNode *&Tem)
{
	if (Tem==NULL)
		return 0;
	int dl=Deep(Tem->Lchild);
	int dr=Deep(Tem->Rchild);
	if (abs(dl-dr)>1)
		Flag=1;
	return 1+max(dl,dr);
}

int main()
{
	TreeNode *Root;
	Root=Built();
	Deep(Root);
	cout << (Flag?"no!":"yes!");
	return 0;
}
