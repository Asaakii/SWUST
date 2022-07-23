#include <iostream>

using namespace std;

int main()

{
	int count[1000];
	for (int i=0;i<1000;i++)
	{
		count[i]=0;
	}
	int n;
	cin >> n;
	int m;
	cin >> m;
	int arr[1000][2];
	for (int i=0;i<m;i++)
	{
		cin >> arr[i][0];
		cin >> arr[i][1];
		count[arr[i][0]]++;
	}
	
	for (int i=0;i<n;i++)
	{
		cout << count[i] << endl;
	}
	return 0;
}
