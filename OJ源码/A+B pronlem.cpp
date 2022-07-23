#include <stdio.h>
#include <string.h>
int main()
{
	int f(char a[]);
	int x,y;
	char a[10000],b[10000];
	while (~scanf ("%s %s",a,b))
	{
		x=f(a);
		y=f(b);
		printf ("%d\n",x+y);
	}
	return 0;
}
int f(char a[])
{
	int len,n;
	len=strlen(a);
	if (len==1)
		n=a[0]-'0';
	else
		n=(a[0]-'0')*10+(a[1]-'0');
	return n; 
}
