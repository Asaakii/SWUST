#include <stdio.h>

int main()
{
	int n;
	int a[100]={0};
	int k;
	int s1=0;
	int s2=0;
	int p=0;
	scanf ("%d",&n);
	for (int i=0;i<n;i++)
	{
		scanf ("%d",&k);
		a[k]++;
		if (k>s1)
		s1=k;
	}
	for (int i=0;i<s1;i++)
	{
		if (a[i]>s2)
		{
			s2=a[i];
			p=i;
		}
		else if (a[i]=s2)
		{
			if (p>i)
			{
				p=i;
			}
		}
	}
	printf ("%d",p);
}
