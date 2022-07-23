#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int n,a[10000+5],b[10000+5],c[10000+5],k=10;
double t=0;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		b[i]=i;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			if(a[i]>a[j])
			{
				swap(b[i],b[j]);
				swap(a[i],a[j]);
			}
		}
	}
	for(int i=1;i<=n-1;i++)
	{
		t=t+(a[i]*(n-i));
	}
	for(int i=1;i<=n;i++)
	{
		cout<<b[i]<<" ";
	}
	t=t/n;
	cout<<endl;
	cout<<fixed<<setprecision(2)<<t;
	return 0;
}
