#include<stdio.h>
#include<iostream>

using namespace std;

int n,m,a[5000007];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	int l=1,r=n;
	while(l<=r)
	{
		int x=l+(m-a[l])*(r-l)/(a[r]-a[l]);
		if(a[x]==m) 
		{
			cout<<x<<endl;
			return 0;
		}
		else if(a[x]<m)
		{
			l=x+1;
		}
		else
		{
			r=x-1;
		}
	}
	cout<<-1<<endl;
	return 0;
}
