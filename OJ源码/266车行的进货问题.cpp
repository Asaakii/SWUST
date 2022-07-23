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
			while (num - k > 0)//��1 2 4 8 .������˳�������
			{
				weight[iCount++] = val * k;
				num -= k;
				k = k * 2;
			}
			weight[iCount++] = val * num;
		}
		for (i = 0; i < iCount; i++)
		{
			for (k = volume; k >= weight[i]; k--)//�ɵ͵��߽��и��¼���ʱ�䣬���4С�� 1 2���������Ѿ������ĸ����ˣ�����Ҫ//�ٴ��ж�����ʱ�䣬ֱ���ж���tl
			{
				dp[k] = dp[k] > dp[k - weight[i]] + weight[i]? dp[k] : dp[k - weight[i]] + weight[i];
			}
		}
		printf("%.2f\n", dp[volume] * moneyRate);
	}
	return 0;
}
