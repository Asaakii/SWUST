#include <bits/stdc++.h>

using namespace std;

int main()
{
	int sum[100]={0},n,x,Sum=0,k;
	cin >> n >> k;
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
		{
			cin >> x;
			if (x)
				sum[i]++;
		}
		if (sum[i]==k)
			Sum++;
	}
	cout << Sum << endl;
	for (int i=0;i<n;i++)
		if (sum[i]==k)
			cout << i;
	return 0;
}
