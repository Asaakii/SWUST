 #include<iostream>
#include<stdio.h>
#include<string.h>
#include<cstring>

using namespace std;
 
int main()
{
	int n;
	int arr[20][20];
	cin >> n;
 
	memset(arr, 0, sizeof(arr));		//置零
	for (int i = 1; i <= n; i++)
	{
		arr[i][1] = arr[1][i] = 1;	//初始化值
	}
 
	for (int i = 2; i <= n; i++)		//动态计算
	{
		for (int j = 2; j <= n; j++)
		{
			arr[i][j] = arr[i][j - 1] + arr[i - 1][j];
		}
	}
	cout << arr[n][n] << endl;
	return 0;
}
