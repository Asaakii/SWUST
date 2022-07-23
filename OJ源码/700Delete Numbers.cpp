#include<stdio.h>
#include<string.h>
int main()
{
	void res(char str[],int num);
	char str[110];
	int num;
	while(scanf("%s%d",str,&num)!=EOF)
	{
		res(str,num);
	}
	return 0;
}

void res(char str[],int num)
{
	int len=strlen(str);
	int i,j,sum=0,k;
	for(i=0;i<num;i++)
	{
		for(j=0;j<len-1;j++)
		{
			if(str[j]>str[j+1])
			{
				break;
			}
		}
		for(j=j;j<len;j++)
		{
			str[j]=str[j+1];
		}
	}
	int flag=0;
	for(i=0;i<len-num;i++)
	{
		if(str[i]!='0')
			break;
	}
	for(j=i;j<len-num;j++)
	{
		flag=1;
		printf("%c",str[j]);
	}
	if(flag==0)
		printf("0");
	printf("\n");
}
