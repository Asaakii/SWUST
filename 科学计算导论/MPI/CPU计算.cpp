#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

void generate(int n, double** A, double** B);
void calculate(int n, double alpha, double beta, double** A, double** B, double** C);
void clean(int n, double** A, double** B, double** C);

int main(int argc, char* argv[])
{
	srand((unsigned)time(NULL));
	clock_t start_time, end_time;
	int n = 256;
	double alpha = 3.141592, beta = 2.712182;
	double** A = (double**)malloc(sizeof(double*) * n);
	double** B = (double**)malloc(sizeof(double*) * n);
	double** C = (double**)malloc(sizeof(double*) * n);
	for (int i = 0; i < n; i++)
	{
		A[i] = (double*)malloc(sizeof(double) * n);
		B[i] = (double*)malloc(sizeof(double) * n);
		C[i] = (double*)malloc(sizeof(double) * n);
	}

	generate(n, A, B);
	start_time = clock();
	calculate(n, alpha, beta, A, B, C);
	end_time = clock();
	printf("CPUºÄÊ±: %lfºÁÃë\n", (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000);
	clean(n, A, B, C);

	return 0;
}

void generate(int n, double** A, double** B)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			A[i][j] = (rand() & 0xff) / 0.66;
			B[i][j] = (rand() & 0xff) / 0.66;
		}
	}
}

void calculate(int n, double alpha, double beta, double** A, double** B, double** C)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			C[i][j] = alpha * A[i][j] + beta * B[i][j];
		}
	}
}

void clean(int n, double** A, double** B, double** C)
{
	for (int i = 0; i < n; i++)
	{
		free(A[i]);
		free(B[i]);
		free(C[i]);
	}

	free(A);
	free(B);
	free(C);
}