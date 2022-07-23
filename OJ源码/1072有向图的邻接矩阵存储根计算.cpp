#include <bits/stdc++.h>

using namespace std;

int main()
{
	int Map[100][100]={0},n,m,Flag=0,a,b;
	cin >> n;
	
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			cin >> Map[i][j];
			
	for (int i=0;i<n;i++)//floyd算法变形 
		for (int j=0;j<n;j++)
			for (int k=0;k<n;k++)
				if (Map[j][i]&&Map[i][k])//如果j->i,i->k那么j->k。 
					Map[j][k]=1;
					
	for (int i=0;i<n;i++)
	{
		int sum=0;
		for (int j=0;j<n;j++)
			if (Map[i][j]&&i!=j)
				sum++;
		if (sum==n-1)
			cout << i;
	}
	return 0;
}
