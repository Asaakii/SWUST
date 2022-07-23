#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<math.h>
#include<string>
#include<string.h>

using namespace std;
 
int link[20][20];
 
struct Point
{
	Point(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0)	//构造函数
	{
		this->x1 = x1;	this->y1 = y1;
		this->x2 = x2;	this->y2 = y2;
	}
	int x1, y1;
	int x2, y2;
 
	void read()
	{
		cin >> x1 >> y1 >> x2 >> y2;
	}
}point[15];
 
int cross(int x1, int y1, int x2, int y2)	//△x、△y;线段斜率比较
{
	return x1 * y2 - x2 * y1;
}
 
int intersection(Point A, Point B)			//判断线段相交
{	//共线不相交
	if (max(A.x1, A.x2) < min(B.x1, B.x2) || max(A.y1, A.y2) < min(B.y1, B.y2) || max(B.x1, B.x2) < min(A.x1, A.x2) || max(B.y1, B.y2) < min(A.y1, A.y2))
		return 0;

	int c[4];
	//判断线段是否在另一条线段的一边，即判断是否相交
	c[0] = cross(A.x2 - A.x1, A.y2 - A.y1, B.x1 - A.x1, B.y1 - A.y1);
	c[1] = cross(A.x2 - A.x1, A.y2 - A.y1, B.x2 - A.x1, B.y2 - A.y1);/*两个分别组合*/
	c[2] = cross(B.x2 - B.x1, B.y2 - B.y1, A.x1 - B.x1, A.y1 - B.y1);
	c[3] = cross(B.x2 - B.x1, B.y2 - B.y1, A.x2 - B.x1, A.y2 - B.y1);
	//上面两个组合得斜率差值，同号则不相交，异号则相交
	if (c[0] * c[1] <= 0 && c[2] * c[3] <= 0)	
		return 1;
	return 0;
}
 
void makeTable(int n)
{	
	memset(link, 0, sizeof(link));	//每次都要初始化
 
	for (int i = 1; i <= n; i++)	//初始化表
	{
		link[i][i] = 1;				//自己相交
		for (int j = 1 + 1; j <= n; j++)
		{
			if (intersection(point[i], point[j]))
			{
				link[i][j] = 1;		//对称
				link[j][i] = 1;
			}
		}
	}
 
	for (int k = 1; k <= n; k++)	//Floyd算法、找出可达路径
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (link[i][k] == 1 && link[k][j] == 1)
					link[i][j] = 1;
			}
		}
	}
}
 
int main()
{
	int n;
	while (cin >> n)
	{
		for (int i = 1; i <= n; i++)	//输入每个线段的位置
			point[i].read();
 
		makeTable(n);
		int a, b;
		while (cin >> a >> b && a | b)	//按为或运算，即a、b至少一个不为零就行
		{
			if (link[a][b] == 1)
				cout << "CONNECTED" << endl;
			else
				cout << "NOT CONNECTED" << endl;
		}
	}
	return 0;
}
