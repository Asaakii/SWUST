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
	int start = 0, end = 100;//������ʼֵΪ1������ֵΪ100
	double delta = 0.0;//��ʼ��delta
	delta = end - start;
	const int  x = 200000000;//ƽ����ֵ��ƽ�ֵķ���
	delta /= x;//����ƽ��ÿ��֮��ľ���
	double time;
	MPI_Init(0, 0);//��MPI��ʼ��
	MPI_Comm_size(MPI_COMM_WORLD, &sizeNum);//��ȡMPI����
	MPI_Comm_rank(MPI_COMM_WORLD, &rankID);//��ȡ��ǰ��MPI�еĺ���
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
				//��ȡ�����������Ľ��
				MPI_Recv(&sum_time, 1, MPI_DOUBLE, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				//��ȡ������������ʱ��
				sum0 += get;//ͳ����������Ľ��
				if (max_time < sum_time)
					max_time = sum_time;//ȡ���ֵ
			}
			double e_time = MPI_Wtime();
			if (max_time < e_time - s_time)
				max_time = e_time - s_time;//��������ȡ�������ֵ
			printf("�����Χ��%d��%d��%lf\n", start, end, sum0);//����������
			printf("�ó�����󻨷�ʱ��Ϊ%lf\n", max_time);//������������л�������ʱ��
		}
		else
		{

			for (int i = (rankID - 1) * n; i < rankID * n && i < x; i++)
			{
				double area = (f(start + i * delta) + f(start + (i + 1) * delta)) / 2 * delta;//����ó�ÿ��С�����ֵ
				sum1 += area;//��С����Ľ�������ۼ�
			}
			MPI_Send(&sum1, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);//���ֲ���������0��
			double e_time = MPI_Wtime();//��¼��������ʱ��
			double u_time = e_time - s_time;
			MPI_Send(&u_time, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);//���ͼ���ʱ���0��
			printf("����ó�%d�������%lf������ʱ��Ϊ%lf\n", rankID, sum1, u_time);//����ó��Ľ��
			MPI_Finalize();//����MPI
		}
	}
	else
	{
		printf("���в���2������������");//����2���������У������˳�����
	}

	return 0;
}
