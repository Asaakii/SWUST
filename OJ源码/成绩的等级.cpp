#include <stdio.h>
int main()
{
	int a;
	scanf ("%d",&a);
	if (a>100)
		printf ("error!\n");
	if (a<60)
		printf ("E");
	if (a>=60&&a<70)
		printf ("D");
	if (a>=70&&a<80)
		printf ("C");
	if (a>=80&&a<90)
		printf ("B");
	if (a>=90&&a<=100)
		printf ("A");
	return 0;
}
