#include <stdio.h>

int m[2000005];

int main()
{
	int k,n,date[100],i;
	scanf("%d %d",&k,&n);
	for(i = 0;i < n; i++) 
		scanf("%d",&date[i]);
	m[1] = 1;
	int t = 2;
	while(1)
	{
		m[t] = t;
		for(i = 0;i < n; i++)
		{
			if(date[i]>t) 
				continue;
			if(m[t]>m[t-date[i]]+1)
			{
				m[t] = m[t-date[i]]+1;
			}
		}
		if(m[t]>k) break;
		t++;
	}
	printf("%d\n",t-1);
}
