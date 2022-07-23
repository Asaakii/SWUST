#include <bits/stdc++.h>

using namespace std;

#define CRL(a) memset(a,0,sizeof(a))
#define MAX 0xfffffff

typedef unsigned long long LL;
typedef long long ll;
const double P1=acos(-1);
const double e=exp(1.0);
const int mod=1e9+7;

typedef struct node
{
	int date;
	node *next;
} LinkNode;

void Create (LinkNode *&Head,int n)
{
	Head=(LinkNode *)malloc(sizeof(LinkNode));
	LinkNode *p1,*p2;
	p1=p2=Head;
	for (int i=0;i<n;i++)
	{
		p1=(LinkNode *)malloc(sizeof(LinkNode));
		cin >> p1->date;
		if (i==0)
			Head->next=p1;
		p2=p1;
	}
	p2->next=NULL;
}

int main()
{
	LinkNode *Head;
	
	int len;
	cin >> len;
	Create(Head,len);
	
	int n;
	cin >> n;
	
	n<1||n>len? cout << "error":cout << "ok";
	
	return 0;
}
