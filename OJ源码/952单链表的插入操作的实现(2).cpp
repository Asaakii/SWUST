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

void Create (LinkNode *&Head,int n)
{
	Head=(LinkNode *) malloc(sizeof(LinkNode));
	LinkNode *p1,*p2;
	p1=p2=Head;
	for (int i=0;i<n;i++)
	{
		p1=(LinkNode *) malloc(sizeof(LinkNode));
		cin >> p1->data;
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
	while(p1!=NULL)
	{
		cout << p1->data << " ";
		p1=p1->next;
	}
}
	
void Insert(LinkNode *Head,int add,int x)
{
	LinkNode *p1=Head,*tem;
		
	for (int i=1;i<add;i++)
		p1=p1->next;
			
	tem=(LinkNode *) malloc(sizeof(LinkNode));
	tem->data=x;
	tem->next=p1->next;
	p1->next=tem;
}
	
int main()
{
	LinkNode *Head;
		
	int len;
	cin >>len;
	Create(Head,len);
	int a,b;
	cin >> a >> b;
	if (a<=0||a<len)
		cout << "error!";
	else
	{
		Insert(Head,a,b);
		Put(Head);
	}
	return 0;
}
