//�����򽫼���׺�������ʽ�������Ԫʽ�����ʽ��ֻ��+��*�����
#include "stdio.h"
#include "ctype.h"
char ch;
int T(int *p);
int F(int *p);
int E1(int p,int *t);
int T1(int p,int *t);
int NEWT()//����һ����ʱ������˳�����A��B��...��Z��������26����ʱ����
{ static int i=64;//����iΪ��̬������ȷ���´ε���ʱiΪ�ϴε��õĽ��
  i=i+1;
  return(i);
}
//����ʽE��t��T��pE'��p�ķ����ӳ���tΪ�ۺ�����,�β���ָ�����
int E(int *t)   
{  int es=0;
   int p;
   es=T(&p);//������T�ӳ���
   es=E1(p,t);//������E1�ӳ���  
   return(es);
}
//����ʽE'��p��t��+T��r @ADD��p,r,t E'��p��t ��E'��p��t���ŷ����ӳ���
//pΪ�̳�����,�β������ͱ���,tΪ�ۺ�����,�β���ָ�����
int E1(int p,int *t)  
{	int r,es,t0;
	if (ch=='+')
	{  ch=getchar();
       es=T(&r);
       t0=NEWT();//����һ����ʱ����
	   printf("      ADD %c,%c,%c\n",p,r,t0);
	   es=E1(t0,t);
	   return(es);
    }  else 
	{	*t=p;
		return(0);
	}
}
//����ʽT��p��F��pT'��p�ķ����ӳ���tΪ�ۺ�����,�β���ָ�����
int T(int *t)   
{  int es=0,p;
   es=F(&p);//������F�ӳ���
   es=T1(p,t);//������T1�ӳ���
   return(es);
}
//����ʽT'��p��t��*F��r @MULT��p,r,t T' ��T'��p��t���ŷ����ӳ���
//pΪ�̳�����,�β������ͱ���,tΪ�ۺ�����,�β���ָ�����
int T1(int p,int *t)   
{
	int r,es,t0;
	if (ch=='*')
	{  ch=getchar();
       es=F(&r);
	   t0=NEWT();//����һ����ʱ����
       printf("      MULT %c,%c,%c\n",p,r,t0);
	   es=T1(t0,t);
	   return(es);
    }  else 
	{	*t=p;
		return(0);
	}
}
//����ʽF��p ->(E��p) |ID��p�ķ����ӳ���pΪ�ۺ�����,�β���ָ�����
int F(int *p)//����F�ӳ���
{  int es=0;
   if (ch=='(')
   {
      ch=getchar();
      es=E(p);//������E�ӳ���
      if (ch!=')') return(3);
      else {ch=getchar();return(es);}
   } else
   {
	if (isalpha(ch)) //�ж��Ƿ�Ϊ��ĸ
	{   *p=ch;
	    ch=getchar();
		return(es);
	} else return(4);
   }
}
//������
main()
{
	int es=0,t;
    printf("�������������ʽ(������ֻ���ǵ�����ĸ)��");
	ch=getchar();
	printf("�����ԪʽΪ��\n");
	es=E(&t);//���������ʽE�ķ������
	if (es==0) printf("\n����ɹ�!\n");
	else printf("\n���ʽ���﷨����!\n");
}


