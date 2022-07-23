#include <bits/stdc++.h>

using namespace std;

int main()
{
	int Map[100][100],n,a,b;
	cin >> n >> a >> b;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			cin >> Map[i][j];
	cout << (Map[a][b]?"yes":"no");
	return 0;
}
