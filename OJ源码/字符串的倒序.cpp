#include <stdio.h>
#include <string.h>

int main()
{
	char s[6];
	while(~scanf("%s", s))
	{
		if (s>10000&&s<100000)
			printf ("5");
		if (s>1000&&s<10000)
			printf ("4");
		if (s>100&&s<1000)
			printf ("3");
		if (s>10&&s<100)
			printf ("2");
		if (s>1&&s<10)
			printf ("1");
		int n;
		n=strlen(s);
		for(int i=n-1; i>=0; i--)
		{
			printf("%c\n", s[i]);
		}
	}
	return 0;
}
