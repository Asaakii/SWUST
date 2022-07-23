#include <stdio.h>
int main()
{
	int p,a[500],b[500];
	int n,i,t1,t2,s1,s2;
	while (~scanf ("%d",&p))
	{
		t1=0;t2=0;
		s1=0;s2=0;
		scanf ("%d",&n);
		for (i=0;i<n;i++)
		{
			scanf ("%d",&a[i]);
			t1+=a[i];
			if (t1>=p)
				s1++;
		}
		for (i=0;i<n;i++)
		{
			scanf ("%d",&b[i]);
			t2+=b[i];
			if (t2>=p)
				s2++;
		}
		s1=n-s1;
		s2=n-s2;
		if (t1<p&&t2<p)
			printf ("None\n");
		else
		{
			if (s1<s2||(t2<p&&t1>=p))
				printf ("xiaoL\n");
			else if (s1==s2)
				printf ("Both\n");
			else
				printf ("xiaoQ\n");
		}
	}
	return 0;	
}
