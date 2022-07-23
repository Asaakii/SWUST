#include <stdio.h>
#include <math.h>
int main()
{
	int r,a,b,c;
	float s1,s2,p;
	while (~scanf ("%d %d %d %d",&r,&a,&b,&c))
	{
		s1=r*r*3.14;
		p=(a+b+c)/2;
		s2=sqrt(p*(p-a)*(p-b)*(p-c));
		if (s1>s2)
			printf ("A\n");
		else
			printf ("B\n");
	}
	return 0;
}
