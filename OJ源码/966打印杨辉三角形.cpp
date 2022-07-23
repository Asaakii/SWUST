#include <iostream>
#include <queue>

using namespace std;

int main()
{
	queue<int> Q;
	int n;
	cin >> n;
	Q.push(1);
	for (int i=1;i<n+1;i++)
	{
		for (int j=1;j<=i;j++)
		{
			cout << Q.front();
			if (j==1)
			{
				Q.push(1);
				if (i!=1)
				{
					Q.pop();
					Q.push(1+Q.front());
				}
			}
			else if (j==i)
			{
				Q.pop();
				Q.push(1);
			}
			else
			{
				int x=Q.front();
				Q.pop();
				Q.push(x+Q.front());
			}
			cout << " ";
		}
		cout << endl;
	}
	return 0;
}
