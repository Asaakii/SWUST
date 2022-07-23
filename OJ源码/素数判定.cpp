#include <stdio.h>
int main()
{
	int a,b,t,s,d=0;
	int c[]={2,3,5,7,11,13,17,19,23,29,31};
	int i,j;
	while (~scanf ("%d %d",&a,&b))
	{
		if (b<a)
		{
			t=b;
			b=a;
			a=t;
		}
		for (i=0;i<=b;i++)
		{
			if (i<32)
			{
				s=0;
				for (j=0;c[j]<i;j++)
				{
					if ((i%c[j])==0)
						s++;
				}
				if (s<1)
					d++;
			}
			else
			{
				s=0;
				for (j=0;j<11;j++)
				{
					if ((i%c[j])==0)
						s++;
				}
				if (s<1)
					d++;
			}
		}
		printf ("%d\n",d);
		d=0;
	}
	return 0;
}
