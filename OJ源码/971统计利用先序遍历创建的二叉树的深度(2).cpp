#include <bits/stdc++.h>

using namespace std;

#define CRL(a) memset(a,0,sizeof(a))
#define NewNode (TreeNode *) malloc (sizeof(TreeNode))
#define MAX 0xfffffff

typedef unsigned long long LL;
typedef long long ll;
const double Pi=acos(-1);
const double e=exp(1.0);
const int mod=1e9+7;

typedef struct node
{
	char data;
	node *Lchild,*Rchild;
} TreeNode;

TreeNode *Built()
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

int Deep(TreeNode *&Tem)
{
	if (Tem==NULL)
		return 0;
	return 1+max(Deep(Tem->Lchild),Deep(Tem->Rchild));
}

int main()
{
	TreeNode *Root;
	Root=Built();
	cout << Deep(Root);
	return 0;
}
