#include <bits/stdc++.h>

using namespace std;

int sum=0,mapp[100][100],m,n,book[100][100];
void bfs(int x,int y)
{
	if (mapp[x][y]&&!book[x][y])
	{
		book[x][y]=1;
		bfs(x-1,y);
		bfs(x+1,y);
		bfs(x,y-1);
		bfs(x,y+1);
	}
}
int main()
{
	cin >> m >> n;
	for (int i=1;i<=m;i++)
		for (int j=1;j<=n;j++)
			cin >> mapp[i][j];
			
	for (int i=1;i<=m;i++)
		for (int j=1;j<=n;j++)
			if (mapp[i][j]&&!book[i][j])
			{
				bfs(i,j);
				sum++;
			}
			
	cout << sum;
	return 0;
}
