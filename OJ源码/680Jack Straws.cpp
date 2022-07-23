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
	Point(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0)	//���캯��
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
 
int cross(int x1, int y1, int x2, int y2)	//��x����y;�߶�б�ʱȽ�
{
	return x1 * y2 - x2 * y1;
}
 
int intersection(Point A, Point B)			//�ж��߶��ཻ
{	//���߲��ཻ
	if (max(A.x1, A.x2) < min(B.x1, B.x2) || max(A.y1, A.y2) < min(B.y1, B.y2) || max(B.x1, B.x2) < min(A.x1, A.x2) || max(B.y1, B.y2) < min(A.y1, A.y2))
		return 0;

	int c[4];
	//�ж��߶��Ƿ�����һ���߶ε�һ�ߣ����ж��Ƿ��ཻ
	c[0] = cross(A.x2 - A.x1, A.y2 - A.y1, B.x1 - A.x1, B.y1 - A.y1);
	c[1] = cross(A.x2 - A.x1, A.y2 - A.y1, B.x2 - A.x1, B.y2 - A.y1);/*�����ֱ����*/
	c[2] = cross(B.x2 - B.x1, B.y2 - B.y1, A.x1 - B.x1, A.y1 - B.y1);
	c[3] = cross(B.x2 - B.x1, B.y2 - B.y1, A.x2 - B.x1, A.y2 - B.y1);
	//����������ϵ�б�ʲ�ֵ��ͬ�����ཻ��������ཻ
	if (c[0] * c[1] <= 0 && c[2] * c[3] <= 0)	
		return 1;
	return 0;
}
 
void makeTable(int n)
{	
	memset(link, 0, sizeof(link));	//ÿ�ζ�Ҫ��ʼ��
 
	for (int i = 1; i <= n; i++)	//��ʼ����
	{
		link[i][i] = 1;				//�Լ��ཻ
		for (int j = 1 + 1; j <= n; j++)
		{
			if (intersection(point[i], point[j]))
			{
				link[i][j] = 1;		//�Գ�
				link[j][i] = 1;
			}
		}
	}
 
	for (int k = 1; k <= n; k++)	//Floyd�㷨���ҳ��ɴ�·��
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
		for (int i = 1; i <= n; i++)	//����ÿ���߶ε�λ��
			point[i].read();
 
		makeTable(n);
		int a, b;
		while (cin >> a >> b && a | b)	//��Ϊ�����㣬��a��b����һ����Ϊ�����
		{
			if (link[a][b] == 1)
				cout << "CONNECTED" << endl;
			else
				cout << "NOT CONNECTED" << endl;
		}
	}
	return 0;
}
