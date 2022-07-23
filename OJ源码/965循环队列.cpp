#include <iostream>
#include <queue>
#include <string>

using namespace std;

int main()
{
	string choose;
	queue<int> Q;
	int m;
	cin >> m;
	int n;
	cin >> n;
	for (int i=0;i<n;i++)
	{
		cin >> choose;
		if (choose=="in")
		{
			int a;
			cin >> a;
			if (Q.size()>=m-1);
			else
			Q.push(a);
		}
		else if (choose=="out")
		{
			if (!Q.empty())
			Q.pop();
		}
	}
	while (!Q.empty())
	{
		cout << Q.front() << " ";
		Q.pop();
	}
	return 0;
}
