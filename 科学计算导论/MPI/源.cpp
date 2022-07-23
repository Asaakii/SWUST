#include<stdio.h>
#include"mpi.h"
#include<iostream>
#include<windows.h>
double f(double x)
{
	return 3.0 + 2.345 * x + 0.98372 * x * x + 0.3221 * x * x * x;
}
int  main()
{
	int sizeNum, rankID;
	int start = 0, end = 100;//设置起始值为1，结束值为100
	double delta = 0.0;//初始化delta
	delta = end - start;
	const int  x = 200000000;//平均差值，平分的份数
	delta /= x;//计算平均每份之间的距离
	double time;
	MPI_Init(0, 0);//将MPI初始化
	MPI_Comm_size(MPI_COMM_WORLD, &sizeNum);//获取MPI数量
	MPI_Comm_rank(MPI_COMM_WORLD, &rankID);//获取当前在MPI中的号码
	if (sizeNum > 1)
	{
		int n = x / (sizeNum - 1);
		double s_time = MPI_Wtime();
		double sum0 = 0, sum1 = 0;
		double get = -1;
		int source = 0;
		double  max_time = 0, sum_time = 0;
		if (rankID != 0)
		{
			for (source = 1; source < sizeNum; source++)
			{
				MPI_Recv(&get, 1, MPI_DOUBLE, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				//获取其他号码计算的结果
				MPI_Recv(&sum_time, 1, MPI_DOUBLE, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				//获取其他号码运算时间
				sum0 += get;//统计其他号码的结果
				if (max_time < sum_time)
					max_time = sum_time;//取最大值
			}
			double e_time = MPI_Wtime();
			if (max_time < e_time - s_time)
				max_time = e_time - s_time;//并行运算取运算最大值
			printf("面积范围是%d到%d有%lf\n", start, end, sum0);//输出计算面积
			printf("得出的最大花费时间为%lf\n", max_time);//输出并行运算中花费最大的时间
		}
		else
		{

			for (int i = (rankID - 1) * n; i < rankID * n && i < x; i++)
			{
				double area = (f(start + i * delta) + f(start + (i + 1) * delta)) / 2 * delta;//计算得出每个小区域的值
				sum1 += area;//对小区域的结果进行累加
			}
			MPI_Send(&sum1, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);//将局部计算结果给0号
			double e_time = MPI_Wtime();//记录运算结果的时间
			double u_time = e_time - s_time;
			MPI_Send(&u_time, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);//输送计算时间给0号
			printf("计算得出%d的面积是%lf，所用时间为%lf\n", rankID, sum1, u_time);//输出得出的结果
			MPI_Finalize();//结束MPI
		}
	}
	else
	{
		printf("并行不足2，请重新设置");//至少2个才能运行，否则退出程序
	}

	return 0;
}
