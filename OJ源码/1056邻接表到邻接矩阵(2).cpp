#include <bits/stdc++.h>

using namespace std;

int main()
{
	int Map[100][100]={0},n,x;
	char t;
	cin >> n;
	for (int i=0;i<n;++i)
	{
		do
		{
			scanf ("%d%c",&x,&t);
			Map[i][x]=1;
		}while (t==' ');
	}
	
	for (int i=0;i<n;++i)
	{
		for (int j=0;j<n;++j)
			printf ("%d",Map[i][j]);
		printf ("\n");
	}
	return 0;
}
