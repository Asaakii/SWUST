#include <bits/stdc++.h>

using namespace std;

#define CRL(a) memset(a,-1,sizeof(a))

int main()
{
	int a[105];
	CRL(a);
	int n,m,num,k,cont=0;
	cin >> n >> m;
	for (int i=0;i<m;i++)
	{
		cin >> num;
		int t=num%n;
		while (a[t]!=-1)
			t=(t+1)%n;
			
		a[t]=num;
	}
	cin >> k;
	int t=k%n;
	for (int i=0;i<n;i++)
	{
		cont++;
		if (a[t]==k)
		{
			cout << t << "," << cont;
			return 0;
		}
		else
			t=(t+1)%n;
	}
	cout << "-1";
	return 0;
}
