#include <bits/stdc++.h>

using namespace std;

#define CRL(a) memset(a,0,sizeof(a))
#define MAX 0xfffffff

typedef unsigned long long LL;
typedef long long ll;
const double Pi=acos(-1);
const double e=exp(1.0);
const int mod=1e9+7;

typedef struct node
{
	char data;
	node *next;
} LinkNode;

void Create (LinkNode *&Head,int n)
{
	LinkNode *p1,*p2;
	p1=(LinkNode *)malloc(sizeof(LinkNode));
	getchar();
	scanf ("%c",&p1->data);
	Head=p2=p1;
	
	for (int i=0;i<n;i++)
	{
		p1=(LinkNode *)malloc(sizeof(LinkNode));
		scanf ("%c",&p1->data);
		p1->next=p1;
		p2=p1;
	}
	p2->next=NULL;
}

void Put(LinkNode *Head)
{
	LinkNode *p1=Head;
	while(p1!=NULL)
	{
		cout << p1->data << " ";
		p1=p1->next;
	}
}

void Reverse(LinkNode *&Head,int n)
{
	LinkNode * p1=Head->next,*p2=p1->next;
	Head->next=NULL;
	for (int i=1;i<n;i++)
	{
		p1->next=Head;
		Head=p1;
		p1=p2;
		p2=p2->next;
	}
}

int main()
{
	LinkNode *Head;
	
	int len;
	cin >> len;
	Create(Head,len);
	Reverse(Head,len);
	Put(Head);
	return 0;
}
