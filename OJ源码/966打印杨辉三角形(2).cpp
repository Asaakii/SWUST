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
	q->front=q->rear=0;
	q->MaxSize=500;
}

bool Empty(SqQueue *&q)
{
	return (q->front==q->rear);
}

int GetSum(SqQueue *&q)
{
	return (q->data[q->front+1]+q->data[q->front+2]);
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
	int n;
	cin >> n;
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=i-2;j++)
		{
			int sum=GetSum(q);
			if (!Into(q,sum))
				break;
			int e;
			if (!deQueue(q,e))
				break;
		}
		if (Into(q,1))
		{
			for (int j=1;j<=i;j++)
				cout << q->data[q->front+j] << " ";
			cout << endl;
		}
	}
	return 0;
}
