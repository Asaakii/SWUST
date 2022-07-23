#include <stdio.h>
int main()
{
	int A,B,C,D;
	while(scanf ("%d %d %d %d",&A,&B,&C,&D)!=EOF)
	{
		if (4*C*C+4*A*A*A*C+18*A*A*A*A*B-18*A*A*D-8*A*A*A*A*A*A==0)
			printf ("Y\n");
		else
			printf ("N\n");
	}
	return 0;
}
