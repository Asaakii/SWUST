#include <stdio.h>

int erfen(int t)
{
	return t*t+t*4; 
}

int main()
{
	long long t;
	while(scanf("%lld",&t)!=EOF&&t!=0)
	{
		int a=0,b=t;
		while(a<b)
		{
			int mid=(a+b)/2;
			if(erfen(mid)>t)
			b=mid;
			else 
			a=mid+1;
		}
		printf("%lld\n",a-1);
		printf("%d %d %d\n",(a-1)/16,(a-1)%16/4,(a-1)%16%4);
	}
	return 0;
}

