#include <stdio.h>
int main()
{
	int a,b,c;
	int x,y,z;
	int t[3],i;
	while (~scanf ("%d %d %d %d %d %d",&a,&b,&c,&x,&y,&z))
	{
		t[2]=z+c;
		t[1]=b+y;
		t[0]=a+x;
		if (t[2]>=60)
		{
			t[2]-=60;
			t[1]++;
		}
		if (t[1]>=60)
		{
			t[1]-=60;
			t[0]++;
		}
		for (i=0;i<3;i++)
		{
			if (t[i]<10)
				printf ("0%d",t[i]);
			else
				printf ("%d",t[i]);
			if (i==2)
				printf ("\n");
			else
				printf (":");
		}
	}
	return 0;
}
