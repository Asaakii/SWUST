#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int position=0;
int Count=1;
bool find(int x,vector<int> arr,int start,int end,int n)
{
	
	if (x>arr[(start+end)/2])
	{
		if ((start+end)/2+1>n-1)
			return false;
		Count++;
		if (find(x,arr,(start+end)/2+1,end,n))
			return true;
		else
			return false;
	}
	
	if (x<arr[(start+end)/2])
	{
		if ((start+end)/2+1>n-1)
			return false;
		Count++;
		if (find(x,arr,start,(start+end)/2-1,n))
			return true;
		else
		{
			return false;
		}
	}
	if (x==arr[(start+end)/2])
	{
		position=(start+end)/2;
		return true;
	}
}

int main()
{
	int a;
	int n;
	cin >> n;
	vector<int> arr;
	for (int i=0;i<n;i++)
	{
		cin >> a;
		arr.push_back(a);
	}
	int x;
	cin >> x;
	sort(arr.begin(),arr.end());
	if (find(x,arr,0,n-1,n))
		cout << position << endl;
	else
		cout << -1 <<endl;
	cout << Count;
	return 0;
}
