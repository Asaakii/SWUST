#include <stdio.h>
#include <algorithm>

using namespace std;

const int N = 10005;
int a[N], m;
int cmp(int a, int b)
{
	return a >= b;
}
int f(int i)
{
	return a[i] <= m;
}
int find(int l, int r)
{
	int i = l;
	int j = r;
	while(i < j)
	{
		int mind = i+j >> 1;
		if(f(mind))
			j = mind;
		else
			i = mind+1;
	}
	return i;
}

int main()
{
	int n;
	scanf("%d", &n);
	for(int i=0; i<n; i++)
	{
		scanf("%d", &a[i]);
	}
	scanf("%d", &m);
	sort(a, a+n, cmp);
	for(int i=0; i<n; i++)
	{
		if((i+1)%10 == 0)
			printf("%d\n", a[i]);
		else if(i == n-1)
		{
			printf("%d\n", a[i]);
		}
		else
			printf("%d ", a[i]);
	}
	int ans = find(0, n-1);
	if(a[ans] == m)
		printf("%d\n", ans+1);
	else
		printf("no this score!\n");
	return 0;
}
