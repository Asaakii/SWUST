#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <windows.h>
#include <math.h>

double func(double x) //���ֺ���
{
    double f;
    f = 3.0 + 2.345 * x + 0.98372 * x * x + 0.3221 * x * x * x;
    return f;
}

double trap(double b, double a, int n, double h) //��������������ܺ�
{
    double area = 0;
    for (int i = 0; i < n; i++)
    {
        area = area + fabs(h * (func(b + h * i) + func(b + h * (i + 1))) / 2);
    }
    return area;
}

int main()
{
    LARGE_INTEGER start_time; //��ʼʱ��
    LARGE_INTEGER end_time; //����ʱ��
    LARGE_INTEGER fr;

    const int n = 500000; //����������ַ���
    int my_rank, comm_sz; //���̺š�������
    printf("MPI version begins at %d\n", n);
    QueryPerformanceFrequency(&fr);
    QueryPerformanceCounter(&start_time); //��ȡ��ʼʱ��
    double a = 0.1, b = 190; //�������
    
    int local_n; //���θ���
    double h, local_a, local_b; //������ʼλ�úͽ���λ��
    double local_int, total_int; //���̵�����ܺ�

    MPI_Init(NULL, NULL); //mpi��ʼ��
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); //��¼���̺�
    printf("���̺ţ�%d\n ", my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); //��¼������

    h = (a - b) / n; //���εĸ�
    local_n = n / comm_sz; //���̻�������Ĵ���
    local_a = b + my_rank * local_n * h; //���̿�ʼ������
    local_b = local_a + local_n * h; //���̽���������
    local_int = trap(local_a, local_b, local_n, h); //��ǰ����������ܺ�

    if (my_rank != 0)
    {
        MPI_Send(&local_int, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD); //��ǰ���̼��������������ݸ�����0
    }
    else
    {
        total_int = local_int;
        for (int i = 1; i < comm_sz; i++) //���н��̼����������
        {
            MPI_Recv(&local_int, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total_int += local_int;
        }
    }

    if (my_rank == 0) //����0������
        printf("Area from %lf to %lf = %lf\n", a, b, total_int);

    MPI_Finalize();//����
    QueryPerformanceCounter(&end_time);//��ȡ����ʱ��
    printf("MPI��ʱ��%lf ms\n", (end_time.QuadPart - start_time.QuadPart) * 1000 / (double)(fr.QuadPart)); //�����̺�ʱ
    return 0;
}
