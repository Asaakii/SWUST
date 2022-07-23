#include <iostream>
#include <algorithm>

using namespace std;

bool cmp(int a,int b)
{
	return a<b;
}

int main()
{
	int ab[10005],ap[10005];
	int n;
	cin>>n;
	for (int i=0;i<n;i++)
		cin>>ab[i]>>ap[i];
	sort(ab,ab+n,cmp);
	sort(ap,ap+n,cmp);
	
	int s=0;
	for (int i=0;i<n;i++)
	{
		s+=abs(ab[n/2]-ab[i])
		s+=abs(ap[n/2]-ap[i])
	}
	cout<<s<<endl;
	return 0;
}
