#include<bits/stdc++.h> 

using namespace std;

int a[20];
int b[20];
int sum = 0;
int find(int n)
{
	if(n == 0)
		return 1;
	else
		return n * find(n - 1);
}

int main()
{
	int n;
	cin>>n;
	for(int i = 0 ; i < n ;i ++)
	{
		cin>>a[i];
	}
	for(int i = 0 ; i < n ;i++)
	{
		b[a[i]]++;
		int p = 0;
		for(int j = 1 ; j < a[i] ; j++)
		{
			if(b[j] )
				p++;
		}
		sum += (find(n - i -1) * (a[i] - 1 - p));
	}
	cout<<sum<<endl;
	int index = 0;int num = 0;int i,j;
	for( i = n - 1 ; i >= 0 ; i--)
	{
		if(a[i  ] < a[i + 1])
		{
			for( j = n - 1; j > i ; j--)
			{
				if(a[j] > a[i])
				{
					index = j ;
					swap(a[i],a[j]);
					break;
				}
			}
			break;
		}
	}
	sort(a + i + 1,a + n );
	for( i = 0 ; i < n ; i++)
		cout<<a[i]<<' ';
	cout<<endl;
	return 0;
}
