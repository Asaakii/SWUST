#include<iostream>

using namespace std;

int main()
{
	int dis[100];
	int oil[100];
	dis[0] = oil[0] = 0;
	dis[1] = oil[1] = 500;
	
	int i, j;
	for (i = 1; dis[i] <= 1500; i++)
	{
		dis[i+1] = dis[i] + 500 / (2*i + 1);
		oil[i+1] = oil[i] + 500;
	}
	 
	while (1)
	{
		int sum;
		cin >> sum;
		if (sum == 0)
			break;
		for (j = i-1; j > 0 && dis[j] > sum; j--);
		for (int k = 1; j > 0; k++, j--)
		{
			cout << k << "  " << sum - dis[j] << "  " << oil[j] << endl;
		}
	}
	return 0;
}
