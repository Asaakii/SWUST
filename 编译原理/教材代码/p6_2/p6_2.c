#include <stdio.h>
char ch;
void s()//s->0s@0|1s@1|ε
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
void s1()//s->0@0s@0|1s@1|ε
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
	
	
	printf("请输入由0、1组成的字符串：");
	ch=getchar();
	s1();
	printf("\n");
	
}