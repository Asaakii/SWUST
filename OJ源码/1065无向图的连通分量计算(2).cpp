#include <bits/stdc++.h>

using namespace std;

int Fa[1000];

int Find(int x)//找x所在的集合代表 
{
	return Fa[x]==x?x:Fa[x]=Find(Fa[x]);
}

void Union(int a,int b)//合并a，b所在的集合 
{
	int fa=Find(a);
	int fb=Find(b);
	if (fa!=fb)
		Fa[b]=fa;
}

int main()
{
	int n,x,ans=0;
	cin >> n;
	
	for (int i=0;i<n;i++)
		Fa[i]=i;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
		{
			cin >> x;
			if (x)
				Union(i,j);
		}
	for (int i=0;i<n;i++)
		if (Fa[i]==i)
			ans++;
	cout << ans;
}
