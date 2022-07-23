#include <algorithm>
#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

#define MAX 1001
#define INF 1000000001

struct Point
{
	double x, y;
}point[MAX];

int n, temp[MAX];

bool cmp(Point a, Point b)
{
	if (a.x != b.x)
	{
		return a.x < b.x;
	}
	else
	{
		return a.y < b.y;
	}
}

bool cmpy(int a, int b)
{
	return point[a].y < point[b].y;
}

double Min(double a, double b)
{
	return a < b ? a : b;
}

double Distance(int i, int j)
{
	return sqrt((point[i].x - point[j].x) * (point[i].x - point[j].x) + (point[i].y - point[j].y) * (point[i].y - point[j].y));
}

double Marge(int left, int right)
{
	double d = INF;
	if (left == right)
		return d;
	if (left + 1 == right)
	{
		return Distance(left, right);
	}
	int mid = (left + right) / 2;
	double dis_left = Marge(left, mid);
	double dis_right = Marge(mid + 1, right);
	d = Min(dis_left, dis_right);
	int i, j;
	int k = 0;
	for (i = left; i <= right; i++)
	{
		if (fabs(point[i].x - point[mid].x) <= d)
		{
			temp[k++] = i;
		}
	}
	sort(temp, temp + k, cmpy);
		for (i = 0; i < k; i++)
		{
			for (j = i + 1; j < k && point[temp[j]].y - point[temp[i]].y < d; j++)
			{
				double temp_dis = Distance(temp[i], temp[j]);
				if (d > temp_dis)
				{
					d = temp_dis;
				}
			}
		}
	return d;
}

int main()
{
	int n, T;
	cin >> n;
	int i;
	while (n > 0)
	{
		cin >> T;
		for (i = 0; i < T; i++)
		{
			cin >> point[i].x >> point[i].y;
		}
		sort(point, point + T, cmp);
		cout << fixed << setprecision(4) <<Marge(0, T - 1) << endl;
		n--;
	}
	return 0;
}
