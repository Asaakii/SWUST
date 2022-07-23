#include <stdio.h>
#include <math.h>
int main()
{
	int n,i,m,a[100];
	while (~scanf ("%d",&n))
	{
		m=n;
		if (n==0)
			printf ("0\n");
		for (i=0;n!=0;i++)
		{
			a[i]=(n%2)^((n/2)%2);
			n/=2;
		}
		for (i--;i>=0;i--)
			printf ("%d",a[i]);
		printf ("\n");
	}
	return 0;
}
