#include<stdio.h>
#include<ctype.h>
#include<stdlib.h> 
#include<string.h>
int TESTmachine();

int TESTmachine()
{
	
	int es = 0, i, k = 0, codecount, stack[1000], data[1000], stacktop = 0;
	
	char Codein[300], code[1000][20]; //���ڽ��������ļ���
	
	int label[100] = { 0 };
	char lno[4];
	FILE *fin;	//����ָ����������ļ���ָ��
	printf("������Ŀ���ļ���(����·��):");
	scanf("%s", Codein);
	
	if ((fin = fopen(Codein, "r")) == NULL)
	
	{
		printf("\n	��%s����!\n", Codein);
		es = 10;
		return(es);
	}
	codecount = 0;
	i = fscanf(fin, "%s", &code[codecount]);
	while (!feof(fin))
	{
		printf("0000	%d	%s	\n", codecount, code[codecount]);
		i = strlen(code[codecount]) - 1;
		if (code[codecount][i] == ':')
		{
			i = i - 5;
			strncpy(lno, &code[codecount][5], i);
			lno[i] = '\0';
			label[atoi(lno)] = codecount;	//��label�����סÿ����ŵĵ�ַ
			printf("label[	%d]=	%d	\n", atoi(lno), label[atoi(lno)]);
			code[codecount][0] = ':';
			code[codecount][1] = '\0';
			strcat(code[codecount], lno);
			k++;
		}
		codecount++;
		i = fscanf(fin, "%s", &code[codecount]);
	}
	fclose(fin);
	for (i = 0; i < 10; i++)
		printf("label	%d	%d	\n", i, label[i]);

	for (i = 0; i< codecount; i++)
	{
		int l;
		l = strlen(code[i]);
		printf("label[2] =	%d	%d	%s	%d\n", label[2], i, code[i], l);
		if ((l> 1) && (code[i][1] == 'A'))
		{
			strncpy(lno, &code[i][5], l - 5);
			printf("llllllllllabel[2}=%d lho= %s\n", label[2], lno);
			lno[l - 5] = '\0';
			_itoa(label[atoi(lno)], code[i], 10);
			
			printf("%d     %s\n",i, code[i]);
			
		}
	}
	for (k = 0; k < 5; k++)
		printf("label%d %d An", k, label[k]);
	i = 0;
	while (i < codecount)	//ִ��ÿ��ָ��
	{
		printf("code %d %s \n", i, code[i]);
		if (strcmp(code[i], "LOAD") == 0)	  //LOAD D��D�е����ݼ��ص�������ջ
		{
			i++;
			stack[stacktop] = data[atoi(code[i])];
			stacktop++;
		}
		if (strcmp(code[i], "LOADI") == 0)	 //LOADI 8��������ѹ�������ջ
		{
			i++;
			stack[stacktop] = atoi(code[i]);
			stacktop++;
		}
		//STO D��������ջջ����Ԫ���ݴ���0,��ջ����Ԫ���ݱ��ֲ��� 
		if (strcmp(code[i], "STO") == 0)
		{
			i++;
			data[atoi(code[i])] = stack[stacktop - 1];
			printf("sto stack %d\n", stack[stacktop - 1]);
			printf("sto data %d\n", data[atoi(code[i])]);
		}
		//POP�C����Ԫ���ݳ��C 
		if (strcmp(code[i], "POP") == 0)
		{
			stacktop--;
		}
		//��00���ΗC����Ԫ��ջ����Ԫ���ݳ�ջ����ӣ�������ջ�� 
		if (strcmp(code[i], "ADD") == 0)
		{
			stack[stacktop - 2] = stack[stacktop - 2] + stack[stacktop - 1];
			printf("add %d\n", stack[stacktop - 1]);
			stacktop--;
		}
		//SUB ����ջ����Ԫ��ȥջ����Ԫ���ݲ���ջ��������ջ�� 
		if (strcmp(code[i], "SUB") == 0)
		{
			stack[stacktop - 2] = stack[stacktop - 2] - stack[stacktop - 1];
			stacktop--;
		}
		//MULT ����ջ����Ԫ��ջ����Ԫ���ݳ�ջ����ˣ�������ջ�� 
		if (strcmp(code[i], "MULT") == 0)
		{
			stack[stacktop - 2] = stack[stacktop - 2] * stack[stacktop - 1];
			stacktop--;
		}
		//DIV ����ջ����Ԫ��ջ����Ԫ���ݳ�ջ�����,������ջ�� 
		if (strcmp(code[i], "DIV") == 0)
		{
			stack[stacktop - 2] = stack[stacktop - 2] / stack[stacktop - 1];
			stacktop--;
		}
		//BR lab������ת�Ƶ�lab 
		if (strcmp(code[i], "BR") == 0)
		{
			i++;
			i = atoi(code[i]);
		}
		//BRF lab���ջ����Ԫ�߼�ֵ����ջ,��Ϊ��(0)��ת�Ƶ�lab 
		if (strcmp(code[i], "BRF") == 0)
		{
			i++;
			if (stack[stacktop - 1] == 0) i = atoi(code[i]);
			stacktop--;
		}
		//EQ��ջ������Ԫ�����ڱȽϲ���ջ,�����������(1��0)����ջ�� 
		if (strcmp(code[i], "EQ") == 0)
		{
			stack[stacktop - 2] = stack[stacktop - 2] == stack[stacktop - 1];
			stacktop--;
		}
		//NOTEQջ������Ԫ�������ڱȽϲ���ջ�������������(1��0)����ջ�� 
		if (strcmp(code[i], "NOTEQ") == 0)
		{
			stack[stacktop - 2] = stack[stacktop - 2] != stack[stacktop - 1];
			stacktop--;
		}
		//GT ��ջ������ջ������������ջ����ջ����1,������0 
		if (strcmp(code[i], "GT") == 0)
		{
			stack[stacktop - 2] = stack[stacktop - 2] > stack[stacktop - 1];
			stacktop--;
		}
		//LES�ΗC��С��ջ������������ջ����ջ����1,������0 
		if (strcmp(code[i], "LES") == 0)
		{
			stack[stacktop - 2] = stack[stacktop - 2] < stack[stacktop - 1];
			stacktop--;
		}
		//GE��ջ�����ڵ���ջ������������ջ����C����1,������0 
		if (strcmp(code[i], "GE") == 0)
		{
			stack[stacktop - 2] = stack[stacktop - 2] >= stack[stacktop - 1];
			stacktop--;
		}
		//LE��ջ��С�ڵ��ڗC������������ջ����ջ����1,������0 
		if (strcmp(code[i], "LE") == 0)
		{
			stack[stacktop - 2] = stack[stacktop - 2] <= stack[stacktop - 1];
			stacktop--;
		}
		//AND��ջ������Ԫ���߼������㲢��ջ�������������(1��0>����ջ�� 
		if (strcmp(code[i], "AND") == 0)
		{
			stack[stacktop - 2] = stack[stacktop - 2] && stack[stacktop - 1];
			stacktop--;
		}
		//0R��ջ������Ԫ���߼������㲢��ջ�������������(1��0)����ջ�� 
		if (strcmp(code[i], "OR") == 0)
		{
			stack[stacktop - 2] = stack[stacktop - 2] || stack[stacktop - 1];
			stacktop--;
		}
		//NOT��ջ�����߼�ֵȡ�� 
		if (strcmp(code[i], "NOT") == 0)
		{
			stack[stacktop - 1] = !stack[stacktop - 1];
		}
		//IN�ӱ�׼�����豸(����)����һ����������,����ջ 
		if (strcmp(code[i], "IN") == 0)
		{
			printf("���������ݣ�");
			scanf("%d", &stack[stacktop]);
			stacktop++;
		}
		//OUT��ջ����Ԫ���ݳ�ջ�����������׼����豸��(��ʾ��) 
		if (strcmp(code[i], "OUT") == 0)
		{
			printf("������� %d\n", stack[stacktop - 1]);
			stacktop--;
		}
		//STOPִֹͣ��
		if (strcmp(code[i], "STOP") == 0)
		{
			break;
		}
		i++;
		//��ʾջ����
		//for (k=stacktop - 1; k> = 0;k--)
		// printf(" %d\n",stack[k]); 
		printf(" %d %d\n", data[0], data[1]);
	}
	return (es);
}

int main()
{
	int es = 0;
	es = TESTmachine();
}
