#include <bits/stdc++.h>

using namespace std;

int Search(int x,int l,int r,int a[],int &times)
{
	times++;
	int mid=l+r >> 1;
	if (x==a[mid])
		return mid;
	if (l==r)
		return -1;
	return x << a[mid]?Search(x,l,mid,a,times):Search(x,mid+1,r,a,times);
}

int main()
{
	int a[1000],x,times=0,n;
	cin >> n;
	for (int i=0;i<n;i++)
		cin >> a[i];
	cin >> x;
	
	cout << Search(x,0,n-1,a,times) << endl;
	cout << times;
	return 0;
}
