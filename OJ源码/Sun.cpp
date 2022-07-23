#include <stdio.h>
int main()
{
	int N,i,s=0;
	scanf ("%d",&N);
	if (N>0)
	{
		for (i=1;i<=N;i++)
			s=s+i;
		printf ("%d\n",s);
	}
	else
	{
		for (i=N;i<=1;i++)
			s=s+i;
		printf ("%d\n",s);
	}
	return 0;
}
