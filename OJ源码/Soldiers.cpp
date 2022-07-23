#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;

int main()
{
	int x[10001],y[10001];
	int n;
	cin>>n;
	for (int i=0;i<n;i++)
	{
		cin>>x[i]>>y[i];
	}
	sort(x,x+n);
	sort(y,y+n);
	int midY=y[(n+1)/2-1];
	for (int i=0;i<n;i++)
	{
		x[i]-=i;
	}
	sort(x,x+n);
	int midX=x[(n+1)/2-1];
	int total=0;
	for (int i=0;i<n;i++)
	{
		total+=fabs(x[i]-midX)+fabs(y[i]-midY);
	}
	cout<<total<<endl;
	return 0;
}
