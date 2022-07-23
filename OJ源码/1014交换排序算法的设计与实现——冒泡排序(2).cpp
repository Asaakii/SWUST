#include <bits/stdc++.h>

using namespace std;

int main()
{
	int a[1000],n,tem;
	cin >> n;
	for (int i=0;i<n;i++)
		cin >> a[i];
	for (int i=0;i<n-1;i++)
		if (a[i]>a[i+1])
			swap(a[i],a[i+1]);
			
	for (int i=0;i<n;i++)
		cout << a[i] << ' ';
	return 0;
}
