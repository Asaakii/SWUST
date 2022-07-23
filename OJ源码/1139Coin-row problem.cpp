#include <iostream>

using namespace std;

int n,dp[10001],x[10001];

int main()
{
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		cin>>x[i];
	}
	dp[1]=x[1];
	for (int i=2;i<=n;i++)
	{
		dp[i]=max(dp[i-1],dp[i-2]+x[i]);
	}
	cout<<dp[n]<<endl;
	return 0;
}

/*
6
5  1  2  10  6  2
*/

/*
17
*/