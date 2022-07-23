#include <stdio.h>
#include <stdlib.h>
int main()
{
	int a,b,i,t,j,q;
	while(scanf("%d %d",&a,&b)!=EOF)
	{
		if(a>b)
		{
			t=a;
			a=b;
			b=t;
		}
		for(i=a,q=0;i<=b;i++)
		{
			for(j=2;j<=i;j++)
				if(i%j==0)
					break;
				if(j==i)
					q=q+1;
		}
		printf("%d\n",q);
	}
	return 0;
}
