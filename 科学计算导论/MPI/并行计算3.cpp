#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <windows.h>
#include <math.h>

double func(double x) //积分函数
{
    double f;
    f = 3.0 + 2.345 * x + 0.98372 * x * x + 0.3221 * x * x * x;
    return f;
}

double trap(double b, double a, int n, double h) //所有梯形面积的总和
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
    LARGE_INTEGER start_time; //开始时间
    LARGE_INTEGER end_time; //结束时间
    LARGE_INTEGER fr;

    const int n = 500000; //区域面积划分份数
    int my_rank, comm_sz; //进程号、进程数
    printf("MPI version begins at %d\n", n);
    QueryPerformanceFrequency(&fr);
    QueryPerformanceCounter(&start_time); //获取开始时间
    double a = 0.1, b = 190; //面积区间
    
    int local_n; //梯形个数
    double h, local_a, local_b; //进程起始位置和结束位置
    double local_int, total_int; //进程的面积总和

    MPI_Init(NULL, NULL); //mpi初始化
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); //记录进程号
    printf("进程号：%d\n ", my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); //记录进程数

    h = (a - b) / n; //梯形的高
    local_n = n / comm_sz; //进程划分面积的次数
    local_a = b + my_rank * local_n * h; //进程开始定义域
    local_b = local_a + local_n * h; //进程结束定义域
    local_int = trap(local_a, local_b, local_n, h); //当前梯形面积的总和

    if (my_rank != 0)
    {
        MPI_Send(&local_int, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD); //当前进程计算出来的面积传递给进程0
    }
    else
    {
        total_int = local_int;
        for (int i = 1; i < comm_sz; i++) //所有进程计算的面积相加
        {
            MPI_Recv(&local_int, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total_int += local_int;
        }
    }

    if (my_rank == 0) //进程0输出面积
        printf("Area from %lf to %lf = %lf\n", a, b, total_int);

    MPI_Finalize();//结束
    QueryPerformanceCounter(&end_time);//获取结束时间
    printf("MPI耗时：%lf ms\n", (end_time.QuadPart - start_time.QuadPart) * 1000 / (double)(fr.QuadPart)); //各进程耗时
    return 0;
}
