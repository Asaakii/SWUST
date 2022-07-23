#include <stdio.h>
int main()
{
	int m,n;
	float a,b;
	int i;
	scanf ("%d %d",&m,&n);
	b=0;
	a=m;
	for (i=0;i<n;i++)
	{
		b=b+a;
		a=a/2;
		b=b+a;
	}
	b=b-a;
	printf ("%.2f %.2f\n",a,b);
	return 0;
}
