#include <iostream>
#include <queue>

using namespace std;

int m,n;
int find(int i,int j,int arr[100][100],queue<int> &Q)
{
	if ((i+1<m?arr[i+1][j]:0)!=0)
	{
		arr[i+1][j]=0;
		find(i+1,j,arr,Q);
	}
	if ((i-1>=0?arr[i-1][j]:0)!=0)
	{
		arr[i-1][j]=0;
		find(i-1,j,arr,Q);
	}
	if ((j+1<n?arr[i][j+1]:0)!=0)
	{
		arr[i][j+1]=0;
		find(i,j+1,arr,Q);
	}
	if ((j-1>=0?arr[j][j-1]:0)!=0)
	{
		arr[i][j-1]=0;
		find(i,j-1,arr,Q);
	}
	if(((j-1>=0?arr[i][j-1]:0)==0)&&((i+1<m?arr[i+1][j]:0)==0)&&((j+1<n?arr[i][j+1]:0)==0)&&((i-1>=0?arr[i-1][j]:0)==0))
		return 0;
}
int main()
{
	int count=0;
	queue<int> Q;
	int arr[100][100];
	cin >> m;
	cin >> n;
	for (int i=0;i<m;i++)
	{
		for (int j=0;j<n;j++)
		{
			cin >> arr[i][j];
		}
	}
	for (int i=0;i<m;i++)
	{
		for (int j=0;j<n;j++)
		{
			if (arr[i][j]!=0)
			{
				arr[i][j]=0;
				find(i,j,arr,Q);
				count++;
			}
		}
	}
	cout << count;
	return 0;
}
