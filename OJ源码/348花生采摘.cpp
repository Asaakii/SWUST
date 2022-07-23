#include<stdio.h>
#include<stdlib.h>

#include<iostream>
#include<math.h>
#include<algorithm>

using namespace std;

typedef struct node
{
	int i;
	int j;
	int number;
}NODE;

NODE a[505];

bool cmp(NODE a,NODE b)
{
	return a.number>b.number;
}

int main()
{
	int n,m,time,len=0;
	cin>>n>>m>>time;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			int t;
			cin>>t;
			if(t!=0)
			{
				a[len].number=t;
				a[len].i=i;
				a[len].j=j;
				len++;
			}
		}
	}
	sort(a,a+len,cmp);
	time=time-2;
	int i_dex=0,j_dex=0,ans=0;
	for(int i=0;i<len;i++)
	{
		int need=0;
		if(i==0)
		{
			need=a[i].i+1;
		}
		else
		{
			need=abs(a[i].i-i_dex)+abs(a[i].j-j_dex)+1;
		}
		if(time>=need+a[i].i)
		{
			i_dex=a[i].i;
			j_dex=a[i].j;
			time-=need;
			ans+=a[i].number;
		}
		else
		{
			break;
		}
	} 
	cout<<ans<<endl;
	return 0;
}
