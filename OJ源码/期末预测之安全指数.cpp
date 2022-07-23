#include <iostream>

using namespace std;

int main()
{
	int n,w,s,R=0;
	cin>>n; 
	for (int i=0;i<n;i++)
	{
		cin>>w>>s;
		R+=w*s;
	}
	if (R>0)
	{
		cout<<R;
	}
	else
		cout<<"0";
	return 0;
	
 } 
