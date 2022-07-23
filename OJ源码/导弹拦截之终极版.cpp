#include <stdio.h>
int main()
{
	int n,k,i,m,t;
	while (~scanf ("%d %d",&n,&k))
	{
		m=0;
		for (i=0;i<n;i++)
		{
			scanf ("%d",&t);
			if (t<=k)
				m++;
		}
		printf ("%d\r\n",m);
	}
	return 0;
}
