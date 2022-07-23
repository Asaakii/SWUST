#include <bits/stdc++.h>

using namespace std;

#define CRL(a) memset(a,0,sizeof(a))
#define MAX 0xfffffff

typedef unsigned long long LL;
typedef long long ll;
const double Pi=acos(-1);
const double e=exp(1.0);
const int mod=1e9+7;

typedef struct
{
	int date[100];
	int len;
} SqList;

void Create (SqList *&L)
{
	int n;
	cin >> n;
	for (int i=0;i<n;i++)
		cin >> L->date[i];
	L->len=n;
}

void Put(SqList *&La)
{
	for (int i=0;i<La->len;i++)
		cout << La->date[i] << " ";
}

void Insert(SqList *&La,int add,int x)
{
	int Flag=0;
	while (La->date[Flag]!=add&&Flag<La->len)
		Flag++;
		
	if (Flag==La->len)
	{
		La->date[Flag]=x;
	}
	else
	{
		int i=La->len-1;
		while(Flag<=i&&i>=0)
		{
			La->date[i+1]=La->date[i];
			i--;
		}
		La->date[i+1]=x;
	}
	La->len++;
}

int main()
{
	SqList *La;
	La=(SqList *) malloc(sizeof(SqList));
	
	Create(La);
	
	int a,b;
	cin >> a >> b;
	Insert(La,a,b);
	Put(La);
	return 0;
}

