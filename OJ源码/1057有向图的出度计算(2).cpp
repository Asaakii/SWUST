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
	Rear[a]->next=tem;
	tem->next=NULL;
	Rear[a]=tem;
	L[a].data++;
}

int main()
{
	int n,edg,a,b;
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
		Insert(a,b);
	}
	for (int i=0;i<n;i++)
		cout << L[i].data << endl;
	return 0;
}
