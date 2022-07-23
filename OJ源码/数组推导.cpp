#include <iostream>

using namespace std;

int main()
{
	int n,b,last=-1,sum=0,sum2=0;
	cin>>n;
	for (int i=0;i<n;i++)
	{
		cin>>b;
		sum+=b;
		if (b!=last)
			sum2+=b;
		last=b;
	}
	cout<<sum<<endl;
	cout<<sum2<<endl;
	return 0;
 } 
