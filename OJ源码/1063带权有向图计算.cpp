#include <iostream>

using namespace std;

int main()
{
	int count1[100][2];
	int count2[100][2];
	int max=0;
	int min=-1;
	int k;
	cin >> k;
	int arr[100][100];
	for (int i=0;i<k;i++)
	{
		for (int j=0;j<k;j++)
		{
			cin >> arr[i][j];
			if (arr[i][j]>=0&&i!=j)
			{
				if (min==-1)
				{
					min=arr[i][j];
				}
				else if (arr[i][j]<=min)
				{
					min=arr[i][j];
				}
				if (arr[i][j]>=max)
				{
					max=arr[i][j];
				}
			}
		}
	}
	int m=0;
	int n=0;
	for (int i=0;i<k;i++)
	{
		for (int j=0;j<k;j++)
		{
			if (arr[i][j]==max)
			{
				count1[m][0]=i;
				count1[m][1]=j;
				m++;
			}
			if (arr[i][j]==min)
			{
				count2[n][0]=i;
				count2[n][1]=j;
				n++;
			}
		}
	}
	cout << max << endl;
	for (int i=0;i<m;i++)
	{
		cout << '<' << count1[i][0] << " " << count1[i][1] << '>';
	}
	cout << endl;
	cout << min << endl;
	for (int i=0;i<n;i++)
	{
		cout << '<' << count2[i][0] << " " << count2[i][1] << '>';
	}
	return 0;
}
