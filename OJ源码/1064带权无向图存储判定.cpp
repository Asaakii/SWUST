#include <iostream>

using namespace std;

int main()
{
	int flag=1;
	int k;
	cin >> k;
	int arr[100][100];
	for (int i=0;i<k;i++)
	{
		for (int j=0;j<k;j++)
		{
			cin >> arr[i][j];
		}
	}
	for (int i=0;i<k;i++)
	{
		for (int j=0;j<k;j++)
		{
			if (i==j&&arr[i][j]!=0)
				flag=0;
			if (arr[i][j]!=arr[j][i])
				flag=0;
		}
	}
	if (flag==1)
	{
		cout << "yes";
	}
	else
		cout << "no";
	return 0;
}
