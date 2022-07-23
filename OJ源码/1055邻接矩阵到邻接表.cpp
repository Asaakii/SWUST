#include <bits/stdc++.h>

using namespace std;

int main()
{
	int arr[100][100];
	int n;
	cin >> n;
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
		{
			cin >> arr[i][j];
		}
	}
	int m,k;
	for (m=0;m<n;m++)
	{
		for (k=0;k<n;k++)
		{
			if (arr[m][k]==1)
			{
				cout << k;
			}
		}
		cout << endl;
	}
	return 0;
}
