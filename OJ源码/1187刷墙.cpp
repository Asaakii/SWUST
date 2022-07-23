#include<stdio.h>
#include<iostream>
#include<cstring>

using namespace std;

int main()
{
	int q[10000] = { 0 };
	int shua[10000] = { 0 };
	int n;
	while (cin >> n)
	{
		memset(q, 0, sizeof(q));
		memset(shua, 0, sizeof(shua));
		for (int i = 0; i < n; i++)
		{
			int a, b;
			scanf("%d %d", &a, &b);
			q[a] += 1;
			q[b+1] += -1;
 
		}
		int t = 0;
		for (int i = 0; i < 2001; i++)
		{
			t += q[i];
			shua[i] = t;
		}
		cin >> n;
		for (int j = 0; j < n; j++)
		{
			int s, e;
			scanf("%d %d", &s, &e);
			for (int i = s; i <= e; i++)
			{
				printf("%d\r\n", shua[i]);
			}
		}
	}
	return 0;
}
