#include <stdio.h>
char ch;
void s()//s->0s@0|1s@1|��
{
	if (ch=='0') 
	{
		ch=getchar();
		s();
		printf("0");
	} else if (ch=='1')
	{
		ch=getchar();
		s();
		printf("1");
	} 
}
void s1()//s->0@0s@0|1s@1|��
{
	if (ch=='0') 
	{
		printf("0");
		ch=getchar();
		s1();		
	} else if (ch=='1')
	{
		ch=getchar();
		s1();
		printf("1");
	} 
}
main()
{
	
	
	printf("��������0��1��ɵ��ַ�����");
	ch=getchar();
	s1();
	printf("\n");
	
}