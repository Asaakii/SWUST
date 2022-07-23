#include <bits/stdc++.h>

using namespace std;

int main()
{
	map<char,int> M;
	int Map[100][100]={0},n,e,Flag=0;char tem,a,b;
	cin >> n >> e;
	for (int i=0;i<n;i++)
	{
		cin >> tem;
		M.insert(make_pair(tem,i));
	}
	
	while(e--)
	{
		cin >> a >> b;
		Map[M[a]][M[b]]=1;
	}
	
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			for (int k=0;k<n;k++)
				if (Map[j][i]&&Map[i][k])
					Map[j][k]=1;
					
	for (int i=0;i<n;i++)
		if (Map[i][i])
			Flag=1;
			
	cout << (Flag?"yes":"no");
	return 0;
}
