#include <iostream>
#include <queue>

using namespace std;

int main()
{
	queue<int> Q;
	int n,x;
	cin >> n;
	cin >> x;
	for (int i=1;i<=n;i++)
	{
		Q.push(i);
	}
	while (1)
	{
		if (Q.size()==1)
			break;
		for (int i=1;i<=x;i++)
		{
			if (i==x)
			{
				Q.pop();
				i=1;
				if (Q.size()==1)
				{
					break;
				}
			}
			int temp=Q.front();
			Q.pop();
			Q.push(temp);
		}
	}
	cout << Q.front();
	return 0;
}
