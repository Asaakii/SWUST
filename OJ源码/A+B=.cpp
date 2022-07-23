#include <stdio.h>
#include <string.h>

int num1(char a[])
{
	if(strcmp(a,"one") == 0) return 1;
	else if(strcmp(a,"two") == 0) return 2;
	else if(strcmp(a,"three") == 0) return 3;
	else if(strcmp(a,"four") == 0) return 4;
	else if(strcmp(a,"five") == 0) return 5;
	else if(strcmp(a,"six") == 0) return 6;
	else if(strcmp(a,"seven") == 0) return 7;
	else if(strcmp(a,"eight") == 0) return 8;
	else if(strcmp(a,"nine") == 0) return 9;
	else if(strcmp(a,"zero") == 0) return 0;
}
int num2(char a[])
{
	if(strcmp(a,"one") == 0) return 1;
	else if(strcmp(a,"two") == 0) return 2;
	else if(strcmp(a,"three") == 0) return 3;
	else if(strcmp(a,"four") == 0) return 4;
	else if(strcmp(a,"five") == 0) return 5;
	else if(strcmp(a,"six") == 0) return 6;
	else if(strcmp(a,"seven") == 0) return 7;
	else if(strcmp(a,"eight") == 0) return 8;
	else if(strcmp(a,"nine") == 0) return 9;
	else if(strcmp(a,"zero") == 0) return 0;
}
int main()
{
	char a[20];
	while(1)
	{
		int sum=0, sum1=0, sum2=0;
		scanf("%s", a);
		sum1=num1(a);
		scanf("%s", a);
		if(strcmp(a,"+") != 0)
		{
			sum1 = sum1*10 + num1(a);
			scanf("%s", a);
		}
		scanf("%s", a);
		sum2 = num2(a);
		scanf("%s", a);
		if(strcmp(a,"=") != 0)
		{
			sum2 = sum2*10 + num2(a);
			scanf("%s", a);
		}
		sum = sum1 + sum2;
		if(sum == 0)
			break;
		else
			printf("%d\n", sum);
	}
	return 0;
}
