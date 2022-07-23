#include <bits/stdc++.h>

using namespace std;

int n,way[1005],Flag[1005],star,end;
bool Map[1005][1005];

void dfs(int node,int fill)
{
	if (node==end)
	{
		way[fill]=end;
		for (int i=0;i<=fill;i++)
			printf ("%d",way[i]);
		printf ("\n");
		return;
	}
	
	for (int j=0;j<n;j++)
	{
		if (Map[node][j]&&!Flag[j])
		{
			way[fill]=node;
			Flag[node]=1;
			dfs(j,fill+1);
			Flag[node]=0;
		}
	}
	return;
}

int main()
{
	cin >> n >> star >> end;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			cin >> Map[i][j];
	dfs(star,0);
	return 0;
}
