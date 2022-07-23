#include<bits/stdc++.h>

using namespace std;

const int maxn=10005;
int dp[maxn];
int main()
{
	int s,n,w[maxn];
	while(cin>>s>>n)
	{
		memset(dp,0,sizeof(dp));
		for(int i=1;i<=n;i++)
		{
			cin>>w[i];
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=s;j>=w[i];j--)
			{
				dp[j]=max(dp[j],dp[j-w[i]]+w[i]);
			}
		}
		if(dp[s]==s)
		{
			cout<<"YES\n";
		}
		else
		{
			cout<<"NO\n";
		}
	}
	return 0;
}
