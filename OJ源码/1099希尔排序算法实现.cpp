#include <bits/stdc++.h>

using namespace std;

int a[1000],n;
int main()
{
	cin >> n;
	for (int i=0;i<n;i++)
		cin >> a[i];
	int i=0,d=n/2;      //һ�ˣ���������Ϊn/2 
	while (i<d)
	{
		if (a[i]>a[i+d])             //a[i]��a[i+d]Ϊһ�飬ǰ���ں�ͻ� 
			swap (a[i],a[i+d]);
		i++;
	}
	for (int i=0;i<n;i++)
		cout << a[i] << " ";
	return 0;
}
