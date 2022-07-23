#include<bits/stdc++.h>

using namespace std;

const int maxn=1005;
const int maxm=105;

int m,n;
int w[maxn],v[maxn],dp[maxn][maxm];

void solve()
{
	for(int i=0;i<=n+1;i++)
	{
		for(int j=0;j<=m+1;j++)
		{
			dp[i][j]=0;
		}
	}
	for(int i=1;i<=n;i++)
	{
		cin>>w[i]>>v[i];
	}
	for(int i=n;i>=1;i--)
	{
		for(int j=1;j<=m;j++)
		{
			if(j>=w[i])
			{
				dp[i][j]=max(dp[i+1][j],dp[i+1][j-w[i]]+v[i]);
			}
			else
			{
				dp[i][j]=dp[i+1][j];
			}
		}
	}
	if(dp[1][m])
	{
		cout<<dp[1][m]<<endl;
	}
	else
	{
		cout<<0<<endl;
	}
}
void print()
{
	int s=m,t=0;
	for(int i=1;i<=n;i++)
	{
		if(s-w[i]>=0&&dp[i][s]==dp[i+1][s-w[i]]+v[i])
		{
			s-=w[i];
			t++;
		}
	}
	s=m;
	for(int i=1;i<=n;i++)
	{
		if(s-w[i]>=0&&dp[i][s]==dp[i+1][s-w[i]]+v[i])
		{
			s-=w[i];
			t--;
			if(t!=0) 
				cout<<i<<" ";
			else 
				cout<<i<<endl;
		}
	}
}

int main()
{
	while(cin>>m>>n)
	{
		solve();
		print();
	}
	return 0;
}
