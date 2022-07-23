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
	char date;
	node *next;
} LinkNode;

void Create (LinkNode *&Head)
{
	int n;
	cin >> n;
	Head=(LinkNode *)malloc(sizeof(LinkNode));
	LinkNode *p1,*p2;
	p1=p2=Head;
	for (int i=0;i<n;i++)
	{
		p1=(LinkNode *)malloc(sizeof(LinkNode));
		getchar();
		scanf ("%c",&p1->date);
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

void Merge(LinkNode *&Head1,LinkNode *&Head2)
{
	LinkNode *p1=Head1;
	while (p1->next!=NULL)
		p1=p1->next;
		
	p1->next=Head2->next;
}

int main()
{
	LinkNode *Head1,*Head2;
	
	Create(Head1);
	Create(Head2);
	Merge(Head1,Head2);
	Put(Head1);
	return 0;
}
