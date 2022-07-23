#include <bits/stdc++.h>

using namespace std;

int main()
{
	int Map[100][100],n,Max=0,Min=0xfffffff;
	cin >> n;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
		{
			cin >> Map[i][j];
			if (Map[i][j]>0)
			{
				Max=max(Max,Map[i][j]);
				Min=min(Min,Map[i][j]);
			}
		}
	cout << Max << endl;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			if (Map[i][j]==Max)
				printf ("<%d %d>",i,j);
				
	cout << endl << Min << endl;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			if (Map[i][j]==Min)
				printf ("<%d %d>",i,j);
	return 0;
}
