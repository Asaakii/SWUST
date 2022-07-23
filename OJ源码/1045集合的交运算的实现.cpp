#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int main()
{
	queue<int> St;
	int arr1[1000];
	int arr2[1000];
	int n,m;
	cin >> m;
	for (int i=0;i<m;i++)
	{
		cin >> arr1[i];
	}
	cin >> n;
	for (int i=0;i<n;i++)
	{
		cin >> arr2[i];
	}
	for (int i=0;i<m;i++)
	{
		for (int j=0;j<n;j++)
		{
			if (arr1[i]==arr2[j])
			{
				St.push(arr1[i]);
			}
		}
	}
	while (!St.empty())
	{
		cout << St.front() << " ";
		St.pop();
	}
	return 0;
}
