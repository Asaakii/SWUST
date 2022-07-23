#include <stdio.h>
#include <stdlib.h>

int main()
{
    int give,spend,back; 
	int t;
	while(scanf("%d %d",&give,&spend)!=EOF)
	{
		back=give-spend;
		printf("%d\n",back);
		
		t=back/50;
		if(t!=0)
		{
			printf("50*%d",t);
			back=back%50;
		}
		t=back/20;
		if(t!=0)
		{
			printf("+20*%d",t);
			back=back%20;
		}
		t=back/10;
		if(t!=0)
		{
			printf("+10*%d",t);
			back=back%10;
		}
		t=back/5;
		if(t!=0)
		{
			printf("+5*%d",t);
			back=back%5;
		}
		t=back/1;
		if(t!=0)
		{
			printf("+1*%d",t);
		}
		printf("=%d\n",give-spend);
	}
    return 0;
}
