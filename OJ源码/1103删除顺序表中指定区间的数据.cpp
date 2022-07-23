#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int a[100];
	int length;
} Sqlist;

void Initlist(Sqlist *&L)
{
	L=(Sqlist *)malloc(sizeof(Sqlist));
	L->length=0;
}

void Createlist(Sqlist *&L)
{
	int n,i;
	scanf ("%d",&n);
	for (i=0;i<n;i++)
	{
		scanf ("%d",&L->a[i]);
	}
	L->length=n;
}

void Delnolist(Sqlist *&L)
{
	int i,k=0,n,a,b;
	scanf ("%d",&a);
	scanf ("%d",&b);
	n=L->length;
	for (i=0;i<n;i++)
	{
		if (L->a[i]<a||L->a[i]>b)
		{
			L->a[k]=L->a[i];
			k++;
		}
		L->length=k;
	}
}
void outputlist(Sqlist *&L)
{
	int i;
	for (i=0;i<L->length;i++)
	{
		printf ("%d ",L->a[i]);
	}
}

int main()
{
	Sqlist *L;
	Initlist(L);
	Createlist(L);
	Delnolist(L);
	outputlist(L);
	return 0; 
}
