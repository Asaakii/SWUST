#include <stdio.h>
#include <string.h>

int main()
{
	char s[205];
	while(~scanf("%s", s))
	{
		int n;
		n = strlen(s);
		char a[205] = {'s'}, b[205] = {'1'}, c[205] = {'-'};
		int d = 0, e = 0, f = 0;
		for(int i=0; i<n; i++)
		{
			if(s[i] >= 'A' && s[i] <= 'Z' || s[i] >= 'a' && s[i] <= 'z')
			{
				a[d] = s[i];
				d++;
			}
			else if(s[i] >= '0' && s[i] <= '9')
			{
				b[e] = s[i];
				e++;
			}
			else
			{
				c[f] = s[i];
				f++;
			}
		}
		printf("%s\n%s\n%s\n", a, b,c );
	}
	return 0;
}
