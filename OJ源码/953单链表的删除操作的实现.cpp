#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

int main()
{
	list<int> List;
	int n;
	cin >> n;
	int arr[1000];
	for (int i=0;i<n;i++)
	{
		cin >> arr[i];
		List.push_back(arr[i]); 
	}
	int m;
	cin >> m;
	list<int>::iterator iter;
	iter = List.begin();
	if (m>List.size()||m<=1)
	{
		cout << "error!";
		return 0;
	}
	for (int i=1;i!=m&&i<List.size();i++)
	{
		iter++;
	}
	iter--;
	List.erase(iter);
	iter=List.begin();
	for (iter=List.begin();iter!=List.end();iter++)
	{
		cout << *iter <<" ";
	}
	return 0;
}
