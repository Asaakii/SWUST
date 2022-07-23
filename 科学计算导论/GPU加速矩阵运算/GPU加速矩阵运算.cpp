#include<stdio.h>
#include<stdlib.h>
#include <windows.h>
#include <cublas.h>			//引入NVIDIA开发包下的Include目录
#define N 1500				//维度
#pragma comment(lib,"cublas.lib")			//需要额外指定引入库的目录

//矩阵运算函数
void simple_sgemm(int n, float alpha, float beta, float* a, float* b, float* c)
{
	for (int i = 0; i < n; i++)//遍历矩阵行
	{
		for (int j = 0; j < n; j++)//遍历矩阵列
		{
			float prod = 0;
			for (int k = 0; k < n; k++)//遍历同列矩阵行
			{
				prod += a[k * n + i] * b[j * n + k];
			}
			c[j * n + i] = alpha * prod + beta * c[j * n + i];
		}
	}
}

//计算进程耗时函数
double time_con(LARGE_INTEGER start_time, LARGE_INTEGER end_time, LARGE_INTEGER fr)
{
	double a = (double)(end_time.QuadPart - start_time.QuadPart) * 1000;
	double b = (double)(fr.QuadPart);
	return a / b;
}

void main(int argc, char* argv[])
{
	int Sq_N = N * N + 10;	//定义矩阵大小
	cublasStatus status;
	LARGE_INTEGER start_time;	//程序开始时间
	LARGE_INTEGER end_time;		//程序结束时间
	LARGE_INTEGER fr;			//程序时钟频率
	float* h_C_ref;				//定义首次的d_C矩阵
	float* d_A, * d_B, * d_C;
	float* h_A, * h_B, * h_C;	//定义矩阵A B C的地址指针，存储随机生成的矩阵
	float alpha = 1.0, beta = 0.0;
	float diff;					//定义差值
	float Covar = 0;		    //定义协方差
	float Sq_diff = 0;			//定义平方差

	printf("声明各个变量数组，并分配内存……\n");
	//为矩阵h_A,h_B,h_C分配内存
	h_A = (float*)malloc(Sq_N * sizeof(float));
	h_B = (float*)malloc(Sq_N * sizeof(float));
	h_C = (float*)malloc(Sq_N * sizeof(float));

	printf("为ABC三个数组赋随机值……\n");
	for (int i = 0; i < Sq_N; i++)
	{
		h_A[i] = rand() / (float)RAND_MAX;
		h_B[i] = rand() / (float)RAND_MAX;
		h_C[i] = rand() / (float)RAND_MAX;
	}

	printf("初始化CUBLAS……\n");
	status = cublasInit();
	QueryPerformanceFrequency(&fr);

	printf("初始化d_A,d_B,d_C数组……\n");
	//为数组d_A,d_B,d_C分配内存
	status = cublasAlloc(Sq_N, sizeof(d_A[0]), (void**)&d_A);
	status = cublasAlloc(Sq_N, sizeof(d_B[0]), (void**)&d_B);
	status = cublasAlloc(Sq_N, sizeof(d_C[0]), (void**)&d_C);

	printf("将数组数据传输到DEVICE……\n");
	//分配cublas中的Vector内存
	status = cublasSetVector(Sq_N, sizeof(h_A[0]), h_A, 1, d_A, 1);
	status = cublasSetVector(Sq_N, sizeof(h_B[0]), h_B, 1, d_B, 1);
	status = cublasSetVector(Sq_N, sizeof(h_C[0]), h_C, 1, d_C, 1);

	//CPU计算结果
	printf("CPU函数执行结果：\n");
	QueryPerformanceCounter(&start_time);
	simple_sgemm(N, alpha, beta, h_A, h_B, h_C);
	QueryPerformanceCounter(&end_time);
	printf("CPU耗时：%f毫秒\n", time_con(start_time, end_time, fr));

	h_C_ref = h_C;

	//GPU计算结果
	printf("CUBLAS函数执行结果\n");
	cublasGetError();
	QueryPerformanceCounter(&start_time);
	cublasSgemm('n', 'n', N, N, N, alpha, d_A, N, d_B, N, beta, d_C, N);
	QueryPerformanceCounter(&end_time);
	printf("GPU耗时：%f毫秒\n", time_con(start_time, end_time, fr));

	//调用cuBlas计算
	status = cublasGetError();
	//给h_C重新分配内存
	h_C = (float*)malloc(Sq_N * sizeof(float));
	//将cublas计算结果传输到h_C上
	status = cublasGetVector(Sq_N, sizeof(h_C[0]), d_C, 1, h_C, 1);

	printf("两者的计算结果对比：\n");
	for (int i = 0; i < Sq_N; i++)
	{
		diff = h_C_ref[i] - h_C[i];
		Covar += diff * diff;
		Sq_diff += h_C_ref[i] * h_C_ref[i];
	}
	//计算协方差
	Covar = (float)sqrt((double)Covar);
	//计算平方和
	Sq_diff = (float)sqrt((double)Sq_diff);

	printf("协方差：%f\n", Covar);
	printf("平方和：%f\n", Sq_diff);
	printf("对比结果：%s\n", (Covar / Sq_diff < 1e-6f) ? "通过" : "失败");

	//释放各矩阵的内存
	status = cublasFree(d_A);
	status = cublasFree(d_B);
	status = cublasFree(d_C);
	free(h_A);
	free(h_B);
	free(h_C);
	free(h_C_ref);
	status = cublasShutdown();
	printf("设备已关闭\n");
	system("pause");
}