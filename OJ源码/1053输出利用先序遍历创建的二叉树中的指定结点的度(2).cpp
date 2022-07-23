#include <bits/stdc++.h>

using namespace std;

struct node
{
	char data;
	node *Lchild,*Rchild,*parents;
};

node *Built(node *&R)
{
	node *T;
	char tem=getchar();
	if (tem=='#')
		return T=NULL;
	T=new node;
	T->data=tem;
	T->parents=R;
	T->Lchild=Built(T->Lchild);
	T->Rchild=Built(T->Rchild);
	return T;
}

int Ac(node *tem,char x)
{
	if (tem==NULL)
		return 0;
	if (tem->data==x)
	{
		node *T=tem->Rchild;int ans=0;
		while (T!=NULL)
		{
			ans++;
			T=T->Rchild;
		}
		return tem->parents?ans+1:ans;
	}
	else
	{
		Ac(tem->Lchild,x);
		Ac(tem->Rchild,x);
	}
}

int main()
{
	node *root,*tem;
	root=Built(root);
	root->parents=NULL;
	char x;
	cin >> x;
	cout << Ac(root,x);
	return 0;
}
