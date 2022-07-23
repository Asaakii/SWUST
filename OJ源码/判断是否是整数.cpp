#include <stdio.h>
int main()
{
	float n;
	while (scanf ("%f",&n)!=EOF)
	{
		if (n!=(int)n)
			printf ("No\n");
		else
			printf ("Yes\n");
	}
	return 0;	
}
