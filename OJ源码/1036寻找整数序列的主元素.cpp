#include <iostream>

using namespace std;

int main()
{
	int n;
	int arr[1000];
	int count[1000]={-1};
	cin >> n;
	for (int i=0;i<n;i++)
	{
		cin >> arr[i];
	}
	int x;
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
		{
			if (arr[i]==arr[j])
				count[i]++;
		}
	}
	int flag=0;
	for (int i=0;i<n;i++)
	{
		if (count[i]>n/2)
			flag=i;
	}
	if (flag!=0)
		cout << count[flag];
	else
		cout << "-1";
	return 0;
}
