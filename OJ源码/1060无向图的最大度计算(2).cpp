#include <bits/stdc++.h>

using namespace std;

int main()
{
	int sum[100]={0},n,x,Max=0;
	cin >> n;
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
		{
			cin >> x;
			if (x)
				sum[i]++;
		}
		Max=max(sum[i],Max);
	}
	cout << Max << endl;
	for (int i=0;i<n;i++)
		if (sum[i]==Max)
			cout << i;
	return 0;
}
