#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include<algorithm>
#include<iostream>
#include<string.h>

using namespace std;
 
int main()
{
	int n;
	double dp[200][200];
	cin >> n;
	double p;
	cin >> p;
	dp[0][0] = 1.0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			if (j == 0)
				dp[i][j] = dp[i - 1][j] * (1 - p);
			else if (j == i)
				dp[i][j] = dp[i - 1][j - 1] * p;
			else
				dp[i][j] = dp[i - 1][j] * (1 - p) + dp[i - 1][j - 1] * p;
		}
	}
	double ans = 0;
	for (int i = (n + 1) / 2; i <= n; i++)
	{
		ans += dp[n][i];
	}
	cout << ans << endl;
	return 0;
}
