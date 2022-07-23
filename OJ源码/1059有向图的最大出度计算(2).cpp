#include <bits/stdc++.h>

using namespace std;

struct node
{
	int data;
	node *next;
};

node L[100],*Rear[100];

void Insert(int a,int b)
{
	node *tem=new node;
	Rear[a]->data=b;
	tem->next=NULL;
	Rear[a]=tem;
	L[a].data++;
}

int main()
{
	int n,edg,a,b,Max=0,Mi=0;
	cin >> n >> edg;
	for (int i=0;i<n;i++)
	{
		L[i].data=0;
		L[i].next=NULL;
		Rear[i]=&L[i];
	}
	while (edg--)
	{
		cin >> a >> b;
		Insert (a,b);
	}
	
	for (int i=0;i<n;i++)
		Max=max(Max,L[i].data);
	cout << Max << endl;
	for (int i=0;i<n;i++)
		if (L[i].data==Max)
			cout << i;
	return 0;
}
