#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n,a[100],Flag=0;
	cin >> n;
	for (int i=1;i<=n;i++)
		cin >> a[i];
	for (int i=1;i<=n/2;i++)
		if (i*2<n&&a[i*2]<a[i])
		{
			Flag=1;
			break;
		}
	cout << (Flag?"No":"Yes");
	return 0;
}
