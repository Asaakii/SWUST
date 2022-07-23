#include <stdio.h>
#include <string.h>
 
int main()
{
	int i;
	int n;
	int k;
	int val;
	int num;
	int volume;
	int iCount;
	int dp[100001];
	int weight[100001];
	float moneyRate;
 
	while (EOF != scanf("%d%f", &volume, &moneyRate))
	{
		iCount = 0;
		memset(dp, 0, sizeof(dp));
		scanf("%d", &n);
		for (i = 0; i < n; i++)
		{
			scanf("%d%d", &val, &num);
			if (val > volume) continue;
				k = 1;
			while (num - k > 0)//按1 2 4 8 .。。的顺序存起来
			{
				weight[iCount++] = val * k;
				num -= k;
				k = k * 2;
			}
			weight[iCount++] = val * num;
		}
		for (i = 0; i < iCount; i++)
		{
			for (k = volume; k >= weight[i]; k--)//由低到高进行更新减少时间，如比4小的 1 2合起来就已经完美的覆盖了，不需要//再次判定减少时间，直接判定会tl
			{
				dp[k] = dp[k] > dp[k - weight[i]] + weight[i]? dp[k] : dp[k - weight[i]] + weight[i];
			}
		}
		printf("%.2f\n", dp[volume] * moneyRate);
	}
	return 0;
}
