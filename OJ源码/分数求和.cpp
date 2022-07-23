#include<stdio.h>
int main()
{
	float a=1,b=2,c,e,sum=0;
	int N; 
	scanf ("%d",&N);
	for(int i=1;i<=N;i++)
	{
		e=b/a;
		sum=sum+e;
		c=b;
		b=a+b;
		a=c;
	}
	printf("%.2f\n",sum);
	return 0;
}
