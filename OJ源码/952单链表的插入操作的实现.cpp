#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

int main()
{
	list<int> L;
	int n;
	cin >> n;
	int arr[1000];
	for (int i=0;i<n;i++)
	{
		cin >> arr[i];
		L.push_back(arr[i]);
	}
	int m;
	cin >> m;
	int date;
	cin >> date;
	if (m > L.size())
	{
		cout << "error!";
		return 0;
	}
	list<int>::iterator iter;
	iter = L.begin();
	for (int i=1;i<m;i++)
	{
		iter++;
	}
	L.insert(iter,date);
	iter = L.begin();
	for (iter = L.begin();iter != L.end();iter++)
	{
		cout << *iter << " ";
	}
	return 0;
}
