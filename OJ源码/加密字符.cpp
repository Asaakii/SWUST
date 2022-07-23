#include <stdio.h>
#include <string.h>

int main()
{
	int sum;
	char a[100];
	while(~scanf("%s", a))
	{
		sum = strlen(a);
		for(int i=0; i<sum; i++)
		{
			if(a[i]>='a'&&a[i]<='y'||a[i]>='A'&&a[i]<='Y')
				a[i] = a[i] + 1;
			else if(a[i] == 'z')
				a[i] = a[i] - 25;
			else if(a[i] == 'Z')
				a[i] = a[i] - 25;
		}
		printf("%s\r\n", a);
	}
	return 0;
}

