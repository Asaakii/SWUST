#include <stdio.h>

int main()
{
	int i, n, x, sum, num[22];
    scanf("%d%d", &n, &x);
    for (i = 0; i < n + 1; i++)
	{
		scanf("%d", &num[i]);
	}
	if (0 == n)
	{
        sum = 0;
    }
    else
	{
        sum = num[n];
	}
	for (i = n - 1; i >= 0; i--)
	{
        sum = sum * x + num[i];
    }
    printf("%d\n", sum);
}
