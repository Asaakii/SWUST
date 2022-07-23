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
	char data;
	linknode *next;
} LinkStNode;

void Init(LinkStNode *&Top)
{
	Top=(LinkStNode *) malloc (sizeof(LinkStNode));
	Top->next=NULL;
}

void Push(LinkStNode *&Top,char x)
{
	LinkStNode *tem;
	tem=(LinkStNode *) malloc (sizeof(LinkStNode));
	tem->data=x;
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

char GetTop(LinkStNode *&Top)
{
	if (Top->next!=NULL)
		return Top->next->data;
	return '0';
}

int main()
{
	LinkStNode *Top;
	Init(Top);
	char x;
	while (scanf ("%c",&x)&&x!='\n')
	{
		if (GetTop(Top)=='['&&x==']'||GetTop(Top)=='('&&x==')')
			Pop(Top);
		else
			Push(Top,x);
	}
	
	Empty(Top) ? cout << "YES":cout << "NO";
	return 0;
}
