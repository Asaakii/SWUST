#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

int main()
{
	stack<int> St;
	int arr[1000];
	int n;
	cin >> n;
	for (int i=0;i<n;i++)
	{
		cin >> arr[i];
		St.push(arr[i]);
	}
	int x;
	cin >> x;
	
	for (int i=0;i<x&&!St.empty();i++)
	{
		St.pop();
	}
	if (St.empty())
		cout << "-1";
	else
		cout << St.top();
	return 0;
}
