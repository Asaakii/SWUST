#include <bits/stdc++.h>

using namespace std;

struct node
{
	int date;
	node *next;
};
node L[100],*rear[100];

void Insert(node *&t,int k)
{
	node *tem=new node;
	t->next=tem;
	tem->date=k;
	tem->next=NULL;
	t=tem;
}

void Show(int n)
{
	node *p;
	for (int i=0;i<n;i++)
	{
		p=L[i].next;
		while (p!=NULL)
		{
			cout << p->date;
			p=p->next;
		}
		cout << endl;
	}
}

int main()
{
	int n,x;
	cin >> n;
	for (int i=0;i<n;i++)
	{
		L[i].date=i;
		L[i].next=NULL;
		rear[i]=&L[i];
	}
	
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
		{
			cin >> x;
			if (x)
				Insert(rear[i],j);
		}
	Show(n);
	return 0;
}
