#include <bits/stdc++.h>

using namespace std;

#define CRL(a) memset(a,0,sizeof(a))
#define MAX 0xfffffff

typedef unsigned long long LL;
typedef long long ll;
const double Pi=acos(-1);
const double e=exp(1.0);
const int mod=1e9+7;

typedef struct linknode
{
	int data;
	linknode *next;
} LinkStNode;

void Init(LinkStNode *&Top)
{
	Top=(LinkStNode *) malloc (sizeof(LinkStNode));
	Top->next=NULL;
}

void Push(LinkStNode *&Top,int x)//入栈 
{
	LinkStNode *tem;
	tem=(LinkStNode *) malloc (sizeof(LinkStNode));
	tem->data=x;
	tem->next=Top->next;
	Top->next=tem;
}

void Pop(LinkStNode *&Top)//这道题直接写全部出栈 
{
	LinkStNode *tem;
	while (Top->next!=NULL)
	{
		tem=Top->next;
		cout << tem->data;
		Top=Top->next;
	}
}

int main()
{
	int x;
	cin >> x;
	
	if (!x)
		cout << 0;
	else
	{
		LinkStNode *Top;
		Init(Top);
		while(x)
		{
			Push(Top,x%2);
			x/=2;
		}
		Pop(Top);
	}
	
	return 0;
}
