#include <bits/stdc++.h>

using namespace std;

#define CRL(a) memset(a,0,sizeof(a))
#define NewNode (TreeNode *)malloc(sizeof(TreeNode));

typedef struct node
{
	char data;
	node *Lchild,*Rchild;
} TreeNode;

queue <node *> q;

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

void Put(TreeNode *Tem)
{
	q.push(Tem);
	while (!q.empty())
	{
		cout << q.front()->data;
		if (q.front()->Lchild!=NULL)
			q.push(q.front()->Lchild);
		if (q.front()->Rchild!=NULL)
			q.push(q.front()->Rchild);
		q.pop();
	}
}

int main()
{
	TreeNode *Root;
	Root=Built();
	Put(Root);
	return 0;
}
