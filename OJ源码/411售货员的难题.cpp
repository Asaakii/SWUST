#include<iostream>
#include <stdio.h>
#include<algorithm>
#include<math.h>

using namespace std;
 
int n;
int map[21][21];
int dp[21][1 << 21];
 
int main() 
{
	cin >> n;
	for (int i = 0; i < n; i++) 
	{
		for (int j = 0; j < n; j++) 
		{
			cin >> map[i][j];
		}
	}
	
	for (int i = 0; i < n; i++) 
	{
		dp[i][0] = map[i][0];
	}
	//竖着填dp表
	for (int j = 1; j < 1 << (n-1); j++) 
	{
		for (int i = 0; i < n; i++) 
		{
			dp[i][j] = 99999999;
			if (((j >> (i - 1)) & 1) == 1) 
			{
				//已经走过这个村子了；
				continue;
			}
			for (int k = 1; k < n; k++) 
			{
				if ((j >> (k - 1) & 1) == 0) 
				{
					continue;
				}
				dp[i][j] = min(dp[i][j], map[i][k] + dp[k][((1 << (k - 1)) ^ j)]);
			}
		}
	}
	printf("%d\n", dp[0][(1 << (n-1)) - 1]);
	return 0;
}
