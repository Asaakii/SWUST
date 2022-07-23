#include <stdio.h>
int main ()
{
	int x,m,s;
	int i,j;
	while (~scanf ("%d",&x))
	{
		s=0;
		for (i=0;s<x;i++)
		{
			m=1;
			for (j=0;j<i;j++)
			{
				m*=2;
			}
			s+=m;
		}
		printf ("%d\n",i);
	}
	return 0;
}
