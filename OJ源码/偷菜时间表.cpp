#include <stdio.h>
int main()
{
	int n,m[60],h[60];
	char a;
	int i;
	scanf ("%d",&n);
	for (i=0;i<n;i++)
	{
		scanf ("%d%c%d",&h[i],&a,&m[i]);
		if ((m[i]+15)>=60)
		{
			m[i]=m[i]+15-60;
			h[i]++;
		}
		else
			m[i]=m[i]+15;
		if ((h[i]+13)>=24)
			h[i]=h[i]+13-24;
		else
			h[i]=h[i]+13;
	}
	for (i=0;i<n;i++)
		printf ("%d:%d\n",h[i],m[i]);
	return 0;
}
