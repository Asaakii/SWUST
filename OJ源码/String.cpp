#include <stdio.h>
#include <string.h>

int main()
{
	char s[100];
	while(~scanf("%s", s))
	{
		int n;
		n = strlen(s);
		for(int i=0; i<n; i++)
		{
			if(s[i] >= 'A' && s[i] <= 'Z')
				printf("%c", s[i]+32);
			else if(s[i] >= 'a' && s[i] <= 'z')
				printf("%c", s[i]-32);
		}
		printf("\n");
	}
	return 0;
}
