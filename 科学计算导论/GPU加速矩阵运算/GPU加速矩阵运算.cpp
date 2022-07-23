#include<stdio.h>
#include<stdlib.h>
#include <windows.h>
#include <cublas.h>			//����NVIDIA�������µ�IncludeĿ¼
#define N 1500				//ά��
#pragma comment(lib,"cublas.lib")			//��Ҫ����ָ��������Ŀ¼

//�������㺯��
void simple_sgemm(int n, float alpha, float beta, float* a, float* b, float* c)
{
	for (int i = 0; i < n; i++)//����������
	{
		for (int j = 0; j < n; j++)//����������
		{
			float prod = 0;
			for (int k = 0; k < n; k++)//����ͬ�о�����
			{
				prod += a[k * n + i] * b[j * n + k];
			}
			c[j * n + i] = alpha * prod + beta * c[j * n + i];
		}
	}
}

//������̺�ʱ����
double time_con(LARGE_INTEGER start_time, LARGE_INTEGER end_time, LARGE_INTEGER fr)
{
	double a = (double)(end_time.QuadPart - start_time.QuadPart) * 1000;
	double b = (double)(fr.QuadPart);
	return a / b;
}

void main(int argc, char* argv[])
{
	int Sq_N = N * N + 10;	//��������С
	cublasStatus status;
	LARGE_INTEGER start_time;	//����ʼʱ��
	LARGE_INTEGER end_time;		//�������ʱ��
	LARGE_INTEGER fr;			//����ʱ��Ƶ��
	float* h_C_ref;				//�����״ε�d_C����
	float* d_A, * d_B, * d_C;
	float* h_A, * h_B, * h_C;	//�������A B C�ĵ�ַָ�룬�洢������ɵľ���
	float alpha = 1.0, beta = 0.0;
	float diff;					//�����ֵ
	float Covar = 0;		    //����Э����
	float Sq_diff = 0;			//����ƽ����

	printf("���������������飬�������ڴ桭��\n");
	//Ϊ����h_A,h_B,h_C�����ڴ�
	h_A = (float*)malloc(Sq_N * sizeof(float));
	h_B = (float*)malloc(Sq_N * sizeof(float));
	h_C = (float*)malloc(Sq_N * sizeof(float));

	printf("ΪABC�������鸳���ֵ����\n");
	for (int i = 0; i < Sq_N; i++)
	{
		h_A[i] = rand() / (float)RAND_MAX;
		h_B[i] = rand() / (float)RAND_MAX;
		h_C[i] = rand() / (float)RAND_MAX;
	}

	printf("��ʼ��CUBLAS����\n");
	status = cublasInit();
	QueryPerformanceFrequency(&fr);

	printf("��ʼ��d_A,d_B,d_C���顭��\n");
	//Ϊ����d_A,d_B,d_C�����ڴ�
	status = cublasAlloc(Sq_N, sizeof(d_A[0]), (void**)&d_A);
	status = cublasAlloc(Sq_N, sizeof(d_B[0]), (void**)&d_B);
	status = cublasAlloc(Sq_N, sizeof(d_C[0]), (void**)&d_C);

	printf("���������ݴ��䵽DEVICE����\n");
	//����cublas�е�Vector�ڴ�
	status = cublasSetVector(Sq_N, sizeof(h_A[0]), h_A, 1, d_A, 1);
	status = cublasSetVector(Sq_N, sizeof(h_B[0]), h_B, 1, d_B, 1);
	status = cublasSetVector(Sq_N, sizeof(h_C[0]), h_C, 1, d_C, 1);

	//CPU������
	printf("CPU����ִ�н����\n");
	QueryPerformanceCounter(&start_time);
	simple_sgemm(N, alpha, beta, h_A, h_B, h_C);
	QueryPerformanceCounter(&end_time);
	printf("CPU��ʱ��%f����\n", time_con(start_time, end_time, fr));

	h_C_ref = h_C;

	//GPU������
	printf("CUBLAS����ִ�н��\n");
	cublasGetError();
	QueryPerformanceCounter(&start_time);
	cublasSgemm('n', 'n', N, N, N, alpha, d_A, N, d_B, N, beta, d_C, N);
	QueryPerformanceCounter(&end_time);
	printf("GPU��ʱ��%f����\n", time_con(start_time, end_time, fr));

	//����cuBlas����
	status = cublasGetError();
	//��h_C���·����ڴ�
	h_C = (float*)malloc(Sq_N * sizeof(float));
	//��cublas���������䵽h_C��
	status = cublasGetVector(Sq_N, sizeof(h_C[0]), d_C, 1, h_C, 1);

	printf("���ߵļ������Աȣ�\n");
	for (int i = 0; i < Sq_N; i++)
	{
		diff = h_C_ref[i] - h_C[i];
		Covar += diff * diff;
		Sq_diff += h_C_ref[i] * h_C_ref[i];
	}
	//����Э����
	Covar = (float)sqrt((double)Covar);
	//����ƽ����
	Sq_diff = (float)sqrt((double)Sq_diff);

	printf("Э���%f\n", Covar);
	printf("ƽ���ͣ�%f\n", Sq_diff);
	printf("�ԱȽ����%s\n", (Covar / Sq_diff < 1e-6f) ? "ͨ��" : "ʧ��");

	//�ͷŸ�������ڴ�
	status = cublasFree(d_A);
	status = cublasFree(d_B);
	status = cublasFree(d_C);
	free(h_A);
	free(h_B);
	free(h_C);
	free(h_C_ref);
	status = cublasShutdown();
	printf("�豸�ѹر�\n");
	system("pause");
}