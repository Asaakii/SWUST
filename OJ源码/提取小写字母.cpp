#include <stdio.h>
#include <string.h>

int main()
{
	char s[205];
	while(~scanf("%s", s))
	{
		int n;
		n = strlen(s);
		char a[205] = {'s'};
		int d = 0;
		for(int i=0; i<n; i++)
		{
			if(s[i] >= 'a' && s[i] <= 'z')
			{
				a[d] = s[i];
				d++;
			}
		}	 
		printf("%s\n", a);
	}
	return 0;
}
