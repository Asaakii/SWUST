#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
	int myrank, nprocs;
	// 初始化MPI环境
	MPI_Init(&argc, &argv);
	// 获取当前进程在通信器MPI_COMM_WORLD中的进程号
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	printf("Hellow, world! %dth of totalTaskNum = %d\n", myrank, nprocs);
	MPI_Finalize();
	return 0;
}