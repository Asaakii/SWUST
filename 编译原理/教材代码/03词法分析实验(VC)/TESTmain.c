//������
#include <stdio.h>
#include <ctype.h>
extern int TESTscan();
char Scanin[300],Scanout[300]; //���ڽ�����������ļ���
FILE *fin,*fout; //����ָ����������ļ���ָ��
void main(){
	int es=0;
	es=TESTscan();//���ʷ�����
    if (es>0) printf("�ʷ������д�,����ֹͣ!");
	else printf("�ʷ������ɹ�!\n");
}
