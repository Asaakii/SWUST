#include<stdio.h>
#include<string.h>

struct node
{
	int v;
	int w;
}g[105];

int Max(int a, int b)
{
	return a > b ? a : b;
}

int main()
{
	int nCase, nVal;
	int i, j;
	int dp[2005];
	while ((scanf("%d %d", &nCase, &nVal)) != EOF)
	{
		for (i = 0; i < nCase; i++)
			scanf("%d %d", &g[i].v, &g[i].w);
		memset(dp, 0, sizeof(dp));
		for (i = 0; i < nCase; i++)
			for (j = g[i].v; j <= nVal; j++)
				dp[j] = Max(dp[j - g[i].v] + g[i].w, dp[j]);
		printf("%d\n", dp[nVal]);
	}
	return 0;
}
