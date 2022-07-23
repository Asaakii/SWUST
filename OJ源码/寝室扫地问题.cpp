#include <stdio.h>
int main()
{
	int a[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	int year,month,day;
	int i,sum;
	while (scanf ("%d%d%d",&year,&month,&day)!=EOF)
	{
		for (i=0;i<month-1;i++)
			day+=a[i];
		day=day+(year-2007)*365-243;
		if ((year==2008&&month>2)||year>2008)
			day++;
		if (day%7==3)
		{
			printf ("ALL\n");
			continue;
		}
		sum=(day-day/7);
		if (day%7>=3)
			sum--;
		switch (sum%4)
		{
			case 1:printf ("B\n");break;
			case 2:printf ("X\n");break;
			case 3:printf ("H\n");break;
			case 0:printf ("P\n");break;
		}
	}
	return 0;
}
