#include <bits/stdc++.h>

using namespace std;

#define CRL(a) memset(a,0,sizeof(a))
#define MAX 0xfffffff

typedef unsigned long long LL;
typedef long long ll;
const double Pi=acos(-1);
const double e=exp(1.0);
const int mod=1e9+7;

int Weight[200],Mark[200],Max,Flag=0,n;

typedef struct linknode
{
	int sum;
	linknode *next;
} LinkStNode;

void Init(LinkStNode *&Top)
{
	Top=(LinkStNode *) malloc (sizeof(LinkStNode));
	Top->next=NULL;
	Top->sum=0;
}

int GetTop(LinkStNode *&Top)
{
	if (Top->next!=NULL)
		return Top->next->sum;
	return 0;
}

void Push(LinkStNode *&Top,int x)
{
	LinkStNode *tem;
	tem=(LinkStNode *) malloc (sizeof(LinkStNode));
	tem->sum=x+GetTop(Top);
	tem->next=Top->next;
	Top->next=tem;
}

void Pop(LinkStNode *&Top)
{
	LinkStNode *tem;
	tem=Top->next;
	Top->next=Top->next->next;
	free(tem);
}

bool Empty(LinkStNode *&Top)
{
	return (Top->next==NULL);
}

void dfs(LinkStNode *&Top)
{
	if (GetTop(Top)>Max||Flag)
		return;
	if (GetTop(Top)==Max)
	{
		Flag=1;
		return;
	}
	for (int i=0;i<n;i++)
	{
		if (!Mark[i])
		{
			Push(Top,Weight[i]);
			Mark[i]=1;
			dfs(Top);
			Mark[i]=0;
			Pop(Top);
		}
	}
}

int main()
{
	LinkStNode *Top;
	CRL(Mark);
	Init(Top);
	cin >> Max >> n;
	for (int i=0;i<n;i++)
		cin >> Weight[i];
	dfs(Top);
	
	Flag? cout << "yes!":cout << "no!";
	
	return 0;
}
