#include <stdio.h>
int main()
{
	int i,a,b,c,x=0,y=0;
	float j,z=0,sum=0;
	scanf ("%d %d %d",&a,&b,&c);
	for (i=0;i<=a;i++)
		x=x+i;
	for (i=0;i<=b;i++)
		y=y+i*i;
	for (j=1;j<=c;j++)
		z=z+1/j;
	sum=x+y+z;
	printf ("%.2f\n",sum);
	return 0;
}
