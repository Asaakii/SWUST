#include <bits/stdc++.h>

using namespace std;

#define CRL(a) memset(a,0,sizeof(a))
#define MAX 0xfffffff
#define NewNode (SqQueue *)malloc (sizeof(SqQueue))

typedef unsigned long long LL;
typedef long long ll;
const double Pi=acos(-1);
const double e=exp(1.0);
const int mod=1e9+7;

struct SqQueue
{
	int data[500];
	int front,rear,MaxSize;
};

void Init(SqQueue *&q)
{
	q=NewNode;
	cin >> q->MaxSize;
	q->front=q->rear=0;
}

bool Empty(SqQueue *&q)
{
	return (q->front==q->rear);
}

bool Into(SqQueue *&q,int x)
{
	if ((q->rear+1)%q->MaxSize==q->front)
		return false;
		
	q->rear=(q->rear+1)%q->MaxSize;
	q->data[q->rear]=x;
	return true;
}

bool deQueue(SqQueue *&q,int &tem)
{
	if (q->front==q->rear)
		return false;
	q->front=(q->front+1)%q->MaxSize;
	tem=q->data[q->front];
	return true;
}

int main()
{
	SqQueue * q;
	Init(q);
	int n,tem,x;
	char a[10];
	cin >> n;
	while(n--)
	{
		scanf ("%s",a);
		if (a[0]=='i')
		{
			cin >> x;
			Into(q,x);
		}
		else
		deQueue(q,tem);
	}
	
	while (deQueue(q,tem))
		cout << tem << " ";
	return 0;
}
