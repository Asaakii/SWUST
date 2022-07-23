#include <bits/stdc++.h>

using namespace std;

#define CRL(a) memset(a,0,sizeof(a))
#define MAX 0xfffffff

typedef unsigned long long LL;
typedef long long ll;
const double Pi=acos(-1);
const double e=1e9+7;

typedef struct node
{
	int date;
	node *next;
} LinkNode;

void Create (LinkNode *Head,int n)
{
	Head=(LinkNode *) malloc(sizeof(LinkNode));
	LinkNode *p1,*p2;
	p1=p2=Head;
	for (int i=0;i<n;i++)
	{
		p1=(LinkNode *) malloc(sizeof(LinkNode));
		cin >> p1->date;
		if (i==0)
			Head->next=p1;
		p2->next=p1;
		p2=p1;
	}
	p2->next=NULL;
}

void Put(LinkNode *Head)
{
	LinkNode *p1=Head->next;
	while (p1!=NULL)
	{
		cout << p1->date << " ";
		p1=p1->next;
	}
}

void Delete(LinkNode *&Head,int x)
{
	LinkNode *p1=Head,*tem;
	
	for (int i=0;i<x-2;i++)
		p1=p1->next;
		
	p1->next=p1->next->next;
}

int main()
{
	LinkNode *Head;
	
	int len;
	cin >> len;
	Create(Head,len);
	int x;
	cin >> x;
	if (x<=1||x>len)
		cout << "error!";
	else
	{
		Delete(Head,x);
		Put(Head);
	}
	return 0;
}
