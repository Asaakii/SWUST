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

int Count[100]={0},Max=0;

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

void Num(TreeNode *&T,int i)
{
	if (T!=NULL)
	{
		Count[i]++;
		Max=max(Max,Count[i]);
		Num(T->Lchild,i+1);
		Num(T->Rchild,i+1);
	}
}

int main()
{
	TreeNode *Root;
	Root=Built();
	Num(Root,1);
	cout << Max;
	return 0;
}
