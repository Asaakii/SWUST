#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main()
{
	int a[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	int sec;
	while(cin>>sec)
	{
		int day=sec/86400;
		int hour=sec%86400/3600;
		int min=sec%86400%3600/60;
		int s=sec%86400%3600%60;
		int i;
		for(i=1;i<=12;i++)
		{
			if(day>a[i])
			{
				day-=a[i];
			}
			else
				break;
		}
		printf("2009-%02d-%02d %02d:%02d:%02d\n",i,day+1,hour,min,s);
	}
	return 0;
}
