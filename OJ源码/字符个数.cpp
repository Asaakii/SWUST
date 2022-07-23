#include <stdio.h>
int main()
{
	char c;
	int letters=0,space=0,digit=0,other=0;
	while((c=getchar())&&c!='\n')
	{
		//记录字母数 
		if((c>='a'&&c<='z')||(c>='A'&&c<='Z'))
			letters++;
		//记录空格数 
		else if (c==' ')
			space++;
		//记录阿拉伯数字 
		else if (c>='0'&&c<='9')
			digit++;
		//记录其他字符 
		else 
			other++;
	}
	printf("%d %d %d %d\n",letters,digit,space,other);
	return 0;
}
