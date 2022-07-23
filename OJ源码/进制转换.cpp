#include <stdio.h>
#include <stdlib.h>
int main(int argc,char*argv[])
{
	int a[32];
	int i;
	int n,temp;
	while (scanf("%d",&n)!=EOF)
	{
		temp=n;
		i=0;
		do
		{
			a[i]=temp%2;
			temp/=2;
			i++;
		}
		while (temp!=0);
		for (i--;i>=0;i--)
		printf ("%d",a[i]);
		printf ("\n");
		printf ("%o\n",n);
	}
	return 0;
}
