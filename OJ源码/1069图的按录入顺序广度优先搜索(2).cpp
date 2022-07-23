#include <bits/stdc++.h>

using namespace std;

char Node[1000];
int Mark[1000]={0},Map[1000][1000],n;
queue<int> S;

void bfs(int x)
{
	S.push(x);
	while (!S.empty())
	{
		int tem=S.front();
		for (int i=0;i<n;i++)
		{
			if (!Mark[i]&&Map[tem][i])
			{
				S.push(i);
				Mark[i]=1;
			}
		}
		cout << Node[tem];
		S.pop();
	}
}

int main()
{
	char s;
	cin >> n;
	scanf ("%s",Node);
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			cin >> Map[i][j];
	cin >> s;
	int i=0;
	while (Node[i]!=s)
		i++;
	Mark[i]=1;
	bfs(i);
	return 0;
}
