#include <iostream>

using namespace std;

int main()
{
	int arr1[1000];
	int arr2[1000];
	int n,m;
	cin >> n;
	for (int i=0;i<n;i++)
	{
		cin >> arr1[i];
	}
	cin >> m;
	int flag=1;
	int k=n;
	for (int i=0;i<m;i++)
	{
		cin >> arr2[i];
		for (int j=0;j<n;j++)
		{
			if (arr2[i]==arr1[j])
			{
				flag=0;
				break;
			}
		}
		if (flag!=0)
		{
			arr1[k]=arr2[i];
			k++;
		}
		else
		{
			flag=1;
		}
	}
	for (int i=0;i<k;i++)
	{
		cout << arr1[i] << " ";
	}
	return 0;
}
