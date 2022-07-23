#include <stdio.h>
int main()
{
	int a,b,c;
	char ch;
	scanf ("%d%c%d",&a,&ch,&b);
	switch(ch)
	{
		case'+':
			c=a+b;
			printf ("%d+%d=%d\n",a,b,c);
			break;
		case'*':
			c=a*b;
			printf ("%d*%d=%d\n",a,b,c);
			break;
		case'-':
			c=a-b;
			printf ("%d-%d=%d\n",a,b,c);
			break;
		case'/':
			c=a/b;
			printf ("%d/%d=%d\n",a,b,c);
			break;
	}
	return 0;
}
