//�����򽫼���׺�������ʽ����ɲ�����׺���ʽ�����ʽ��ֻ��+��*�����
//�ķ�ΪE->E+T@+��E->T��T->T*F@*��T->F��F->(E)��F->i@i
//����i��Ϊ������ĸ
//ȥ����ݹ飬�޸ĺ��ķ�Ϊ��E->T{+T@+},T->F{*F@*},F->(E)|i@i
#include "stdio.h"
#include "ctype.h"
char ch;
int T();
int F();
int E()   //����E�ӳ��� E->T{+T@+}
{  int es=0;
   es=T();//������T�ӳ���
   while (ch=='+')
   {  ch=getchar();
      es=T();//������T�ӳ���
      printf("+");
      
   }
    return(es);
}
int T()    //������T�ӳ���T->F{*F@*}
{  int es=0;
   es=F();//������F�ӳ���
   while (ch=='*')
   {  ch=getchar();
      es=F();//������F�ӳ���
      printf("*");
     
   }
    return(es);
}
int F()//����F�ӳ���
{  int es=0;
   if (ch=='(')
   {
      ch=getchar();
      es=E();//������E�ӳ���
      if (ch!=')') return(3);
      else {ch=getchar();return(es);}
   } else
   {
	if (isalpha(ch)) //�ж��Ƿ�Ϊ��ĸ
	{   printf("%C",ch);
		ch=getchar();
		return(es);
	} else return(4);
   }
}
main()
{
	int es=0;
    printf("�������������ʽ��������ֻ������ĸ����");
	ch=getchar();
	printf("�����������ʽ��");
	es=E();//���������ʽE�ķ������
	if (es==0) printf("\n����ɹ�!\n");
	else printf("\n���ʽ���﷨����!\n");
}
