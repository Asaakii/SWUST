//������
#include <stdio.h>
#include <ctype.h>
extern int TESTscan();
extern int TESTparse();
char Scanin[300], Scanout[300], Errorfile[300], Codeout[300]; //���ڽ�����������Լ������ļ���
FILE *fin, *fout; //����ָ����������ļ���ָ��
int main()
{
	int es = 0;
	es = TESTscan();//���ʷ�����
	if (es > 0)
		printf("�ʷ������д�,����ֹͣ!");
	else printf("�ʷ������ɹ�!\n");
	if (es == 0)
	{
		es = TESTparse();	//���﷨��������������ɴ���
		if (es == 0)
		{ 
			printf("�﷨��������������ɴ���ɹ�!\n");
		} 
		else
			printf("�﷨��������������ɴ������!\n");
	}
}
