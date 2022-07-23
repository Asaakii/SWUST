#include <stdio.h>
int main()
{
	int N,i,s=1;
	scanf ("%d",&N);
	if (N<0)
		printf ("shuruwuxiao!\n");
	else
	{ 
		for (i=1;i<=N;i++)
			s=s*i;
		printf ("%d\n",s);
	} 
	return 0;
}
