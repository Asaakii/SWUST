#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	int arr[100][100];
	for (int i=0;i<n;i++)
	for (int j=0;j<n;j++)
		arr[i][j]=0;
	getchar();
	char a;
	for (int i=0;i<n;i++)
	{
		while (1)
		{
			a=getchar();
			if (a=='\n')
				break;
			arr[i][a-'0']=1;
		}
	}
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
		{
			cout << arr[i][j];
		}
		cout << endl;
	}
	return 0;
}
