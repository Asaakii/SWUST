#include <stdio.h>
int main()
{
	char c;
	int letters=0,space=0,digit=0,other=0;
	while((c=getchar())&&c!='\n')
	{
		//��¼��ĸ�� 
		if((c>='a'&&c<='z')||(c>='A'&&c<='Z'))
			letters++;
		//��¼�ո��� 
		else if (c==' ')
			space++;
		//��¼���������� 
		else if (c>='0'&&c<='9')
			digit++;
		//��¼�����ַ� 
		else 
			other++;
	}
	printf("%d %d %d %d\n",letters,digit,space,other);
	return 0;
}
