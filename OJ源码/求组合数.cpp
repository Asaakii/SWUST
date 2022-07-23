#include<stdio.h>
#include<math.h>
int Fact(double n,double r)
{
	if(r<=1)
		return n;
	else 
		return Fact(n,r-1)*(n-r+1)/r;
}
int main()
{
	int n,r;
	while(1)
	{
		scanf("%d %d",&n,&r);
		if(n==0&&r==0)
			break;
		if(n<=0||r<0||n<r)
		{
			printf("error!\n");
		}
		else
		{
			printf("%d\n",Fact(n,r));
		}
	}
}
