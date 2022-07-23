#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int flag=0;
	int temp[1000];
	int count=0;
	int n;
	cin >> n;
	for (int i=0;i<n;i++)
	{
		temp[i]=0;
	}
	int arr[100][100];
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
		{
			cin >> arr[i][j];
		}
	}
	for (int i=0,k=1;i<n-1;i++,k++)
	{
		for (int j=k;j<n;j++)
		{
		if (flag==0)
		{
			temp[i]=1;
			temp[j]=1;
			flag=1;
		}
		else
		{
			if (temp[i]==0&&temp[j]==0)
			{
				temp[i]=1;
				temp[j]=1;
				count++;
			}
		}
		}
	}
	cout << count;
	return 0;
}
