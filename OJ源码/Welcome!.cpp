#include <stdio.h>
int main()
{
	int n,i;
	char a;
	scanf ("%d",&n);
	for (i=1;i<=n;i++)
	{
		scanf (" %c",&a);
		getchar();
		printf ("%c\n",a-32);
	 } 
	 return 0;
} 
