#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

int main()
{
	list<int> List;
	int m;
	cin >> m;
	int arr[1000];
	for (int i=0;i<m;i++)
	{
		cin >> arr[i];
		List.push_back(arr[i]);
	}
	list<int>::iterator iter;
	List.sort();
	for (iter=List.begin();iter!=List.end();iter++)
	{
		cout << *iter << " ";
	}
	return 0;
}
