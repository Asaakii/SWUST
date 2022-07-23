#include <bits/stdc++.h>

using namespace std;

int sum=0,Count=1;
struct node
{
	char date;
	node *Lchild;
	node *Rchild;
};

node *Built()
{
	node *T;
	char tem=getchar();
	if (tem=='#')
		return T=NULL;
	sum++;
	T=new node;
	T->Lchild=Built();
	T->Rchild=Built();
	return T;
}

queue <node *> Q;

void Judge()
{
	while (!Q.empty())
	{
		node *tem=Q.front();
		if (tem->Lchild==NULL)
			return;
		Count++;
		Q.push(tem->Lchild);
		if (tem->Rchild==NULL)
			return;
		Count++;
		Q.push(tem->Rchild);
		Q.pop();
	}
}

int main()
{
	node *root=Built();
	Q.push(root);
	Judge();
	cout << (sum==Count?'Y':'N');
	return 0;
}
