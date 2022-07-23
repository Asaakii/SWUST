#include <bits/stdc++.h>

using namespace std;

#define CRL(a) memset(a,0,sizeof(a))

typedef struct node
{
	int data;
	node *pre;
	node *next;
} DLinkNode;

void Create (DLinkNode *&Head,int n)
{
	int x;
	DLinkNode *p1,*p2;
	p1=(DLinkNode *)malloc(sizeof(DLinkNode));
	Head=p2=p1;
	Head->pre=NULL;
	Head->next=NULL;
	
	while(n--)
	{
		cin >> x;p1=Head;
		while (p1->next!=NULL&&p1->next->data<=x)
			p1=p1->next;
			
		p2=(DLinkNode *)malloc(sizeof(DLinkNode));
		p2->data=x;
		p2->pre=p1;
		p2->next=p1->next;
		if (p1->next!=NULL)
			p1->next->pre=p2;
		p1->next=p2;
	}
}

void Put(DLinkNode *Head)
{
	DLinkNode *p1=Head->next;
	while (p1!=NULL)
	{
		cout << p1->data << " ";
		p1=p1->next;
	}
}

int main()
{
	DLinkNode *Head;
	
	int len;
	cin >> len;
	Create (Head,len);
	Put(Head);
	return 0;
}
