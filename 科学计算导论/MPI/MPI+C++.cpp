#include "mpi.h"

#include<iostream>

using namespace std;

int main(void)
{
	int rankID;
	int sizeNum;
	MPI_Init(0, 0);
	MPI_Comm_size(MPI_COMM_WORLD, &sizeNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &rankID);
	cout << "Hello world! " << rankID << " of total =" << sizeNum << endl;
	MPI_Finalize();
	return 0;
}