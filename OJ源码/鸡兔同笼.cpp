#include <stdio.h>
#include <stdlib.h>
int main()
{
	int a,c; //a��ʾ����������ݵ�������c��ʾ����Ľ���
	scanf("%d",&a);
	while(a--)
	{
		scanf("%d",&c);
		if(c%2!= 0) //�������ţ�û�д�
			printf("0 0\n");
		else if(c%4!= 0)    //��Ҫ������Ŀ���٣�ʹ���ﾡ����4ֻ��
							//��Ҫ������Ŀ��࣬ʹ���ﾡ����2ֻ��
			printf("%d %d\n",c/4+1, c/2);
		else
			printf("%d %d\n",c/4, c/2);
	}
	return 0;
}
