//������
#include <stdio.h>
#include <ctype.h>
extern int TESTscan();
extern int TESTparse();
char Scanin[300],Scanout[300]; //���ڽ�����������ļ���
FILE *fin,*fout; //����ָ����������ļ���ָ��
int main(){
	int es=0;
	es=TESTscan();//���ʷ�����
    if (es>0) printf("�ʷ������д�,����ֹͣ!");
	else printf("�ʷ������ɹ�!\n");
	if (es==0) 
	{		
  		es=TESTparse();	//���﷨����
		if (es==0) 	printf("�﷨�����ɹ�!\n");
		else	printf("�﷨��������!\n");
	}
}
