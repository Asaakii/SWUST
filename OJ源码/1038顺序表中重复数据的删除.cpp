#include <iostream>

using namespace std;

int main()
{
	int arr[100][100];
	int n;
	cin >> n;
	for (int i=0;i<n;i++)
	{
		cin >> arr[i][0];
	}
	int x;
	cin >> x;
	for (int i=0;i<n;i++)
	{
		if (arr[i][0]==x)
		{
			arr[i][1]=1;
		}
	}
	int count=0;
	for (int i=0;i<n;i++)
	{
		if (arr[i][1]!=1)
			cout << arr[i][0] << " ";
		else
			count++;
	}
	if (count==n)
		cout << "-1";
	return 0;
}
