#include <bits/stdc++.h>

using namespace std;

int main()
{
	int Map[100][100]={0},n,m,Flag=0,a,b;
	cin >> n >> m;
	while (m--)
	{
		cin >> a >> b;
		Map[a][b]=1;
	}
	
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			for (int k=0;k<n;k++)
			{
				if (Map[j][i]&&Map[i][k])
					Map[j][k]=1;
			}
			
	for (int i=0;i<n;i++)
		for (int j=0;j<i;j++)
			if (Map[i][j]!=Map[j][i])
				Flag=1;
	cout << (Flag?"no":"yes");
	return 0; 
}
