#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

typedef struct node
{
	int data[1005];
	int length;
}List;
void startList(List *&L)
{
	L=(List *)malloc(sizeof(List));
	L->length=0;
}
int main()
{
	List *L,*S;
	startList(L);
	startList(S);
	while(cin>>L->length)
	{
		int num=L->length;
		int i,k=0;
		for(i=0;i<L->length;i++)
			cin>>L->data[i];
		for(i=L->length-1;i>0;i--)
		{
			if(L->data[i]<L->data[0])
				S->data[k++]=L->data[i];
		}
		S->data[k++]=L->data[0];
		for(i=1;i<L->length;i++)
		{
			if(L->data[i]>L->data[0])
				S->data[k++]=L->data[i];
		}
		for(i=0;i<num;i++)
			cout<<S->data[i]<<" ";
	}
	return 0;
}
