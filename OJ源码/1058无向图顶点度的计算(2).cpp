#include <bits/stdc++.h>

using namespace std;

int main()
{
	int sum=0,n,x;
	cin >> n;
	for (int i=0;i<n;i++)
	{
		sum=0;
		for (int j=0;j<n;j++)
		{
			cin >> x;
			if (x)
				sum++;
		}
		cout << sum <<endl;
	}
	return 0;
}
