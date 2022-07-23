#include <stdio.h>
#include <string.h>

int main()
{
	int x,z;
	while (scanf("%d,%d",&x,&z))
	{
		int a[1005]={0};
		a[z]=x;
		if (x==0&&z==0)
			break;
		while (1)
		{
			scanf ("%d,%d",&x,&z);
			a[z]=a[z]+x;
			if (x==0&&z==0)
				break;
		}
		while (1)
		{
			scanf ("%d,%d",&x,&z);
			a[z]=a[z]+x;
			if (x==0&&z==0)
				break;
		}
		int f=0;
		for (int i;i<1005;i++)
		{
			if (a[i])
			{
				if (f)
					printf ("+");
				printf ("%dx^%d",a[i],i);
				f=1;
			}
		}
	}
	return 0;
}
