#include <stdio.h>
int main()
{
	int f(int a);
	int a,b;
	while (~scanf ("%d %d",&a,&b))
	{
		a=f(a);
		b=f(b);
		printf ("%d\n",a+b);
	}
	return 0;
}
int f(int a)
{
	int b=0;
	while (a>0)
	{
		b=b*10+a%10;
		a=a/10;
	}
	return b;
}

