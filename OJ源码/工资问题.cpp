#include<stdio.h>
#include<stdlib.h>
int main()
{
	int a,b,c;
	scanf ("%d %d",&a,&b);
	if (a>=0&&a<=40)
		c=a*b;
	if (a>40&&a<=60)
		c=40*b+(a-40)*b*1.5;
	if (a>60)
		c=40*b+20*b*1.5+(a-60)*3*b;
	printf ("%g",c);
	if (a<0||a>168)
		printf ("input id wrong!");
	return 0;
 } 
