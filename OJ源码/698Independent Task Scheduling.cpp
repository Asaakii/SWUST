#include <iostream>

using namespace std;

int main()
{
	int n,dp[10001];
	int sumA=0,ans=999999999;
	int a[201],b[201];
	cin>>n;
	for (int i=0;i<n;i++)
	{
		cin>>a[i];
		sumA+=a[i];
		dp[i]=0;
	}
	for (int i=0;i<n;i++)
	{
		cin>>b[i];
	}
	for (int k=0;k<n;k++)
	{
		for (int i=sumA;i>=0;i--)
		{
			if (i>=a[k])
			{
				dp[i]=min(dp[i]+b[k],dp[i-a[k]]);
			}
			else
				dp[i]+=b[k];
		}
	}
	for (int i=0;i<=sumA;i++) 
	{
		int t=max(i,dp[i]);
		ans=min(ans,t);
	}
	cout<<ans<<endl;
	return 0;
}

/*
6
2 5 7 10 5 2
3 8 4 11 3 4
*/

/*
15
*/