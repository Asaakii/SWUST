#include <iostream>

using namespace std;

int n,m;
int a[10001][10001],dp[10001][10001];
int main()
{
	cin>>n>>m;
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
		{
			cin>>a[i][j];
		}
	}
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
		{
			dp[i][j]=max(dp[i-1][j],dp[i][j-1])+a[i][j];
		}
	}
	cout<<dp[n][m]<<endl;
	return 0;
}
