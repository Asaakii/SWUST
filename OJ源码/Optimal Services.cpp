#include <stdio.h>
int main()
{
	int a[10000];
	int i,j,t;
	float averg;
	float s=0;
	int n;
	scanf ("%d",&n);
	for (i=0;i<n;i++)
		scanf ("%d",&a[i]);
	for (i=0;i<(n-1);i++)
	{
		for (j=i+1;j<n;j++)
		{
			if (a[i]<a[j])
			{
				t=a[i];
				a[i]=a[j];
				a[j]=t;
			}
		}
	}
	for (i=0;i<n;i++)
		s+=a[i]*(i+1);
	averg=s/n;
	printf ("%.2f\n",averg);
	return 0;
}
