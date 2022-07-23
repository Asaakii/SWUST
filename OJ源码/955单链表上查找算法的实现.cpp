#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

int main()
{
	list<int> List;
	int n;
	int m;
	cin >> n;
	int arr[1000];
	for (int i=0;i<n;i++)
	{
		cin >> arr[i];
		List.push_back(arr[i]);
	}
	cin >> m;
	list<int>::iterator iter;
	iter=List.begin();
	if (m>List.size()||m<1)
	{
		cout << "error";
		return 0;
	}
	int i=1;
	for (;i!=m&&i<List.size();i++)
	{
		if (i==m)
		{
			cout << "ok";
			return 0;
		}
		iter++;
	}
	if (i==m)
	{
		cout << "ok";
		return 0;
	}
	cout << "error";
	return 0;
}
