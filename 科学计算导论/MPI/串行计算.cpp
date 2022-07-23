#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>

double func(double x) //���ֺ���
{
	double f;
	f = 3.0 + 2.345 * x + 0.98372 * x * x + 0.3221 * x * x * x;
	return f;
}

int main()
{
	LARGE_INTEGER start_time; //��ʼʱ��
	LARGE_INTEGER end_time; //����ʱ��
	LARGE_INTEGER fr;

	const int n = 500000; //����������ַ���
	double area = 0; //�������
	double a = 0.1, b = 190; //�������
	double h; //���εĸ�
	h = (a - b) / n;

	QueryPerformanceFrequency(&fr);
	QueryPerformanceCounter(&start_time); //��ȡ��ʼʱ��

	for (int i = 0; i < n; i++)
	{
		area = area + fabs(h * (func(b + h * i) + func(b + h * (i + 1))) / 2);
	}

	QueryPerformanceCounter(&end_time);//��ȡ����ʱ��
	printf("Area is %lf\n", area);
	printf("CPU��ʱ: %lf����\n", (end_time.QuadPart - start_time.QuadPart) * 1000 / (double)(fr.QuadPart));
	return 0;
}
