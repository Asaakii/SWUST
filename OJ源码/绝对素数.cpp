#include <stdio.h>
#include <math.h>
int main()
{
	int i;
	int j,n,m;
	int k,x,y,l;
	for (i=101;i<1000;i+=2)
	{
		m=0;
		l=0;
		n=sqrt(i);
		for (j=3;j<=n;j++)
		{
			if (i%j==0)
				m++;
		}
		if (m==0)
		{
			y=(i%10)*100+(i%100-i%10)+(i-i%100)/100;
			x=sqrt(y);
			for (k=2;k<=x;k++)
			{
				if (y%k==0)
					l++;
			}
			if (l==0)
				printf ("%d\n",i);
		}
	}
	return 0;
}
