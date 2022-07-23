#include <bits/stdc++.h>

using namespace std;

struct Hnode
{
	int data;
	Hnode *next;
}*Rear[1000];

struct Hash
{
	Hnode *Head[1000];
	int len,n;
}L;

void Insert(int x)
{
	Hnode *tem=new Hnode;
	tem->data=x;
	tem->next=NULL;
	int ads=x%L.len;
	if (L.Head[ads])//已经有了就往后放 
		Rear[ads]->next=tem;
	else
		L.Head[ads]=tem;
	Rear[ads]=tem;//更新尾节点地址 
}

int Search(int x)
{
	int ads=x%L.len,Count=1;
	Hnode *tem=L.Head[ads];
	if (tem==NULL)
		return -1;
	while (tem!=NULL&&tem->data!=x)
	{
		tem=tem->next;
		Count++;
	}
	return tem==NULL? -1:Count;
}

void Ac()
{
	int n,x;
	cin >> n;
	L.len=n;
	for (int i=0;i<n;i++)
		L.Head[i]==NULL;
		cin >> n;
		L.n=n;
		while (n--)
		{
			cin >> x;
			Insert(x);
		}
		cin >> x;
		int ans=Search(x);
		
		if (ans!=-1)
			cout << x%L.len << ",";
		cout << ans;
}

int main()
{
	Ac();
	return 0;
}
