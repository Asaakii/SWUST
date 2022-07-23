#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n,a,x;
	cin >> n >> a;cout << n-1 << endl;
	for (int i=0;i<n;i++)
		if (i!=a) cout << i;cout << endl;
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
		{
			cin >> x;
			if (i!=a&&j!=a) cout << x;
		}
	if (i!=a) cout << endl;
	}
	return 0;
}
