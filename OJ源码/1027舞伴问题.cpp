#include <iostream>
#include <queue>

using namespace std;

int main()
{
	queue<char> Q1,Q2;
	int n,m;
	char a;
	cin >> n;
	for (int i=0;i<n;i++)
	{
		cin >> a;
		Q1.push(a);
	}
	cin >> m;
	for (int j=0;j<m;j++)
	{
		cin >> a;
		Q2.push(a);
	}
	int x;                        //¼¸ÂÖÌøÎè 
	cin >> x;
	for (int i=1;i<x;i++)
	{
		char f1=Q1.front();
		char f2=Q2.front();
		Q1.pop();
		Q2.pop();
		Q1.push(f1);
		Q2.push(f2);
	}
	cout << Q1.front() << " " <<Q2.front();
}
