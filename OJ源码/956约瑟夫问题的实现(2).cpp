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
	int data;
	node *next;
} LinkNode;

void Create (LinkNode *Head,int n)
{
	LinkNode *p1,*p2;
	
	p1=(LinkNode *)malloc(sizeof(LinkNode));
	Head=p1;p2=p1;
	p1->data=n;
	for (int i=1;i<n;i++)
	{
		p1=(LinkNode *)malloc(sizeof(LinkNode));
		p1->data=i;
		p2->next=p1;
		p2=p1;
	}
	p2->next=Head;
}

void Work(LinkNode *Head,int n,int k)
{
	LinkNode *p1=Head;
	while(n!=1)
	{
		for (int i=1;i<k;i++)
			p1=p1->next;
		p1->next=p1->next->next;
		n--;
	}
	cout << p1->data;
}

int main()
{
	LinkNode *Head;
	
	int n,k;
	cin >> n >> k;
	Create(Head,n);
	Work(Head,n,k);
	return 0;
}
