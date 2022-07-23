#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>

double func(double x) //积分函数
{
	double f;
	f = 3.0 + 2.345 * x + 0.98372 * x * x + 0.3221 * x * x * x;
	return f;
}

int main()
{
	LARGE_INTEGER start_time; //开始时间
	LARGE_INTEGER end_time; //结束时间
	LARGE_INTEGER fr;

	const int n = 500000; //区域面积划分份数
	double area = 0; //积分面积
	double a = 0.1, b = 190; //面积区间
	double h; //梯形的高
	h = (a - b) / n;

	QueryPerformanceFrequency(&fr);
	QueryPerformanceCounter(&start_time); //获取开始时间

	for (int i = 0; i < n; i++)
	{
		area = area + fabs(h * (func(b + h * i) + func(b + h * (i + 1))) / 2);
	}

	QueryPerformanceCounter(&end_time);//获取结束时间
	printf("Area is %lf\n", area);
	printf("CPU耗时: %lf毫秒\n", (end_time.QuadPart - start_time.QuadPart) * 1000 / (double)(fr.QuadPart));
	return 0;
}
