#include <bits/stdc++.h>

using namespace std;

int main()
{
	int Map[100][100],n,Flag=0;
	cin >> n;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
		{
			cin >> Map[i][j];
			if (i>j&&Map[i][j]!=Map[j][i])
				Flag=1;
		}
	cout << (Flag?"no":"yes");
	return 0;
}
