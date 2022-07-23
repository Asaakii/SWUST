#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

int main()
{
	list<char> List;
	int m;
	cin >> m;
	char arr[1000];
	for (int i=0;i<m;i++)
	{
		cin >> arr[i];
		List.push_back(arr[i]);
	}
	list<char>::iterator iter;
	reverse(List.begin(),List.end());
	for (iter=List.begin();iter!=List.end();iter++)
	{
		cout << *iter << " ";
	}
	return 0;
}
