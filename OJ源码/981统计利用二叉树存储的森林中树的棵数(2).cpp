#include <bits/stdc++.h>

#define NewNode (node*)malloc(sizeof(node))

using namespace std;

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

int Count(node *&root)
{
	return root->Rchild==NULL?1:1+Count(root->Rchild);
}

int main()
{
	node *root=Built();
	cout << Count(root);
	return 0;
}
