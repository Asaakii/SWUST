#include<iostream>
#include<bits/stdc++.h>//万能头文件

using namespace std;

int n;
int str[999];
int Lmax,Lmin;
int Max,Min;
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>str[i];
	}
	Lmax=str[0];
	Max=0;
	Lmin=str[0];
	Min=0;
	for(int i=0;i<n;i++)
	{
		if(str[i]>=Lmax)
		{
			Max=i;
			Lmax=str[i];
		}
		if(str[i]<=Lmin)
		{
		Min=i;
			Lmin=str[i];
		}
	}
	printf("Lmax=%d\n",Max);
	printf("Lmin=%d",Min);//注意此处不再换行
	return 0; 
}

