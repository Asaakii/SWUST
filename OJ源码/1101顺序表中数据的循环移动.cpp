#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int main()
{
	queue<int> Q;
	int arr[1000];
	int n,a;
	cin >> n;
	for (int i=0;i<n;i++)
	{
		cin >> arr[i];
		Q.push(arr[i]);
	}
	int x;
	cin >> x;
	if (x>=n||x<=0)
	{
		cout << "error!";
		return 0; 
	}
	x%=n;
	
	for (int i=0;i<x;i++)
	{
		int x=Q.front();
		Q.pop();
		Q.push(x);
	}
	while (!Q.empty())
	{
		cout << Q.front() << " ";
		Q.pop();
	}
	return 0;
}
