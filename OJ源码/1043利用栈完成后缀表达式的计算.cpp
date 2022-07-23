#include<stdio.h>

int main()
{
	int top=-1;
	int a[100];
	char s;
	while(1)
	{
		scanf("%c",&s);
		if(s=='#')
			break;
		else
		{
			if(s>='0'&&s<='9')
			{
				a[++top]=s-'0';
			}
			else if(s=='+')
			{
				a[--top]+=a[top+1];
			}
			else if(s=='-')
			{
				a[--top]-=a[top+1];
			}
			else if(s=='*')
			{
				a[--top]*=a[top+1];
			}
			else if(s=='/')
			{
				a[--top]/=a[top+1];
			}
		}
	}
	printf("%d",a[top]);
}

