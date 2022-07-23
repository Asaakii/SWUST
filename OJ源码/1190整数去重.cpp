#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>

using namespace std;

int main ()
{
	int n;
	cin>>n;
	int x[n+1];
	memset(x,0,sizeof(x));
	int temp;
	for(int i=1;i<=n;i++)
	{
		cin>>x[i];
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			if(x[i]==x[j]) 
				x[j]=0;
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(x[i]) 
			cout<<x[i]<<" ";
	}
	return 0;
}

