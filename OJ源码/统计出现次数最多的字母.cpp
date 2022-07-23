#include <stdio.h>
#include <string.h>

int main()
{
	int n, sum=0, ll=0;
	scanf("%d", &n);
	char a;
	int b[256] = {0};
	getchar();
	for(int i=0; i<=n; i++)
	{
		scanf("%c", &a);
		sum = a - '0';
		b[sum]++;
	}
	for(int i=0; i<256; i++)
	{
		if(b[i] > ll)
		{
			sum = i;
			ll = b[i];
		}
	}
	a = sum + '0';
	printf("%c\n", a);
	return 0;
}
