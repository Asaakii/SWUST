#include <iostream>

using namespace std;

int main()
{
	int flag=0;
	int m,k;
	int count[100];
	int n;
	cin >> n;
	cin >> m >> k;
	int arr[1000][1000];
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
		{
			cin >> arr[i][j];
			if (arr[i][j]==1&&i==m&&j==k)
				flag=1;
		}
	}
	if (flag==1)
	{
		cout << "yes";
	}
	else
	{
		cout << "no";
	}
	return 0;
}
