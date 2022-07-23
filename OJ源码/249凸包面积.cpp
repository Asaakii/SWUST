#include <stdio.h>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
struct Point
{
	int x;
	int y;
}p[110];
 
double Square(Point a, Point b, Point c)
{
	return (a.x*b.y + b.x*c.y + c.x*a.y - a.x*c.y - b.x*a.y - c.x*b.y)*1.0 / 2;
}
 
bool cmp(Point a, Point b)  
{
	return a.x < b.x;
}

double Solve(int l, int r, int m)  
{
	int mi = -1;
	double mdis = 0;
	for (int i = l + 1; i < r; i++)
	{
		double dis = Square(p[l], p[r], p[i])*m;
		if (dis > mdis)
		{
			mdis = dis;
			mi = i;
		}
	}
	if (mi == -1)
		return 0;
	return Solve(l, mi, m) + Solve(mi, r, m)+mdis;
}
 
int main()
{
	int _t;
	scanf("%d", &_t);
	while (_t--)
	{
		int n;
		cin >> n;
		for (int i = 0; i < n; i++)
			scanf("%d %d", &p[i].x, &p[i].y);
		sort(p, p + n, cmp); 
		printf("%.1lf\n", Solve(0, n - 1, 1)+ Solve(0, n - 1, -1));
	}
	return 0;
}
