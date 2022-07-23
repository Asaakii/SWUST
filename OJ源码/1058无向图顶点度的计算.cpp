#include <iostream>

using namespace std;

int main()
{
	int count[100];
	int n;
	cin >> n;
	int arr[1000][1000];
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
		{
			cin >> arr[i][j];
			if (arr[i][j]==1)
				count[i]++;
		}
	}
	for (int i=0;i<n;i++)
	{
		cout << count[i] << endl;
	}
	return 0;
}
