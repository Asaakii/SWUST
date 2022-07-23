#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int arr1[1000];
	int arr2[1000];
	int m;
	int n;
	vector<int> v1;
	vector<int> v2;
	cin >> m;
	for (int i=0;i<m;i++)
	{
		cin >> arr1[i];
		v1.push_back(arr1[i]);
	}
	cin >> n;
	for (int i=0;i<n;i++)
	{
		cin >> arr2[i];
		v2.push_back(arr2[i]);
	}
	vector<int>::iterator iter;
	for (iter = v2.begin();iter !=v2.end();iter++)
	{
		v1.push_back(*iter);
	}
	sort(v1.begin(),v1.end());
	iter = v1.begin();
	for (iter = v1.begin();iter != v1.end();iter++)
	{
		cout << *iter << " ";
	}
	return 0;
}
