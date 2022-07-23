#include <bits/stdc++.h>

using namespace std;

#define CRL(a) memset(a,0,sizeof(a))
#define MAX 0xfffffff

typedef unsigned long long LL;
typedef long long ll;
const double Pi=acos(-1);
const double e=exp(1.0);
const int mod=1e9+7;

typedef struct qnode
{
	char data;
	struct qnode *next;
}QNode;

typedef struct
{
	QNode * front;
	QNode * rear;
}Head;

void Init(Head *&q)
{
	q=(Head *) malloc (sizeof(Head));
	q->front=q->rear=NULL;
}

bool Empty(Head *&q)
{
	return (q->rear==NULL);
}

void In(Head *&q,char &x)
{
	QNode *p;
	p=(QNode *) malloc(sizeof(QNode));
	p->data=x;
	p->next=NULL;
	if (q->rear==NULL)
		q->front=q->rear=p;
	else
	{
		q->rear->next=p;
		q->rear=p;
	}
}

bool Out(Head *&q,char &x)
{
	QNode *T;
	if (q->rear==NULL)
		return false;
	t=q->front;
	if (q->front=q->rear)
		q->front=q->rear=NULL;
	else
		q->front=q->front->next;
	x=t->data;
	free(t);
	return true;
}

int main()
{
	Head *q1;
	Head *q2;
	Init(q1);
	Init(q2);
	int n;char x,a,b;;
	cin >> n;
	while (n--)
	{
		cin >> x;
		In(q1,x);
	}
	
	cin >> n;
	while(n--)
	{
		cin >> x;
		In(q1,x);
	}
	
	cin >> n;
	while(n--)
	{
		cin >> x;
		In(q2,x);
	}
	
	cin >> n;
	while(n--)
	{
		Out(q1,a);
		Out(q2,b);
		In(q1,a);
		In(p2,a);
	}
	cout << a << " " >> b;
	return 0;
}
