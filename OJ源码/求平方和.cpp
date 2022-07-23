#include<stdio.h>
int f(int n)
{
	if (n)
		return n*n+f(n-1);
	else
		return 0;
}
int main()
{
	int n;
	scanf("%d",&n);
	printf("%d\n",f(n));
}
