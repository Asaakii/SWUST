#include <stdio.h>
#include <stdlib.h>
int main()
{
	int a,c; //a表示输入测试数据的组数，c表示输入的脚数
	scanf("%d",&a);
	while(a--)
	{
		scanf("%d",&c);
		if(c%2!= 0) //有奇数脚，没有答案
			printf("0 0\n");
		else if(c%4!= 0)    //若要动物数目最少，使动物尽量有4只脚
							//若要动物数目最多，使动物尽量有2只脚
			printf("%d %d\n",c/4+1, c/2);
		else
			printf("%d %d\n",c/4, c/2);
	}
	return 0;
}
