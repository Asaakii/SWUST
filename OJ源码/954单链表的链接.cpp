#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

int main()
{
	list<char> List1;
	int n;
	list<char> List2;
	int m;
	char arr1[1000];
	char arr2[1000];
	cin >> n;
	for (int i=0;i<n;i++)
	{
		cin >> arr1[i];
		List1.push_back(arr1[i]);
	}
	cin >> m;
	for (int i=0;i<m;i++)
	{
		cin >> arr2[i];
		List2.push_back(arr2[i]);
	}
	list<char>::iterator iter;
	for (iter=List2.begin();iter!=List2.end();iter++)
	{
		List1.push_back(*iter);
	}
	for (iter=List1.begin();iter!=List1.end();iter++)
	{
		cout << *iter <<" ";
	}
	return 0;
} 
