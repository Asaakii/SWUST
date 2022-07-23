#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
	int myrank, nprocs;
	// ��ʼ��MPI����
	MPI_Init(&argc, &argv);
	// ��ȡ��ǰ������ͨ����MPI_COMM_WORLD�еĽ��̺�
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	printf("Hellow, world! %dth of totalTaskNum = %d\n", myrank, nprocs);
	MPI_Finalize();
	return 0;
}