#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	char arr1[1000];
	int n;
	vector<char> v1;
	cin >> n;
	for (int i=0;i<n;i++)
	{
		cin >> arr1[i];
		v1.push_back(arr1[i]);
	}
	vector<char>::iterator iter;
	reverse(v1.begin(),v1.end());
	for (iter = v1.begin();iter != v1.end();iter++)
	{
		cout << *iter << " ";
	}
	return 0;
}
