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

void Merge (SqList *&La,SqList *&Lb,SqList *&Lc)
{
	int ia=0,ib=0,ic=0;
	while (ia<La->len&&ib<Lb->len)
		Lc->date[ic++]=La->date[ia]<=Lb->date[ib]?La->date[ia++]:Lb->date[ib++];
		//三目运算，就是找date[ia]和date[ib]小的放进C
	while (ia<La->len)
		Lc->date[ic++]=La->date[ia++];//如果B数组放完了，就把A数组剩下的放进去。
	while (ib<Lb->len)
		Lc->date[ic++]=Lb->date[ib++];//如果A数组放完了，就把B数组剩下的放进去。
	Lc->len=La->len+Lb->len;	 //长度相加
}

void Put(SqList *&La)
{
	for (int i=0;i<La->len;i++)
		cout << La->date[i] << " ";
}

int main()
{
	SqList *La,*Lb,*Lc;
	La=(SqList *) malloc(sizeof(SqList));
	Lb=(SqList *) malloc(sizeof(SqList));
	Lc=(SqList *) malloc(sizeof(SqList));
	
	Create(La);
	Create(Lb);
	Merge(La,Lb,Lc);
	Put(Lc);
	return 0;
}
