#include<stdio.h>
#include<iostream>

using namespace std;

int n,a[1007],ans=0;
int max(int close)//�ҵ�closeǰ���������ֵ���±�
{
	int max=-1;
	int t;
	for(int i=0;i<=close;i++)
	{
		if(max<a[i])
		{
			max=a[i];
			t=i;
		}
	}
	return t;
}

void swap(int k)//����k֮ǰ����k��˳�� 
{
	ans++;
	for(int i=0;i<=k/2;i++)
	{
		int te=a[i];
		a[i]=a[k-i];
		a[k-i]=te;
	}
}

int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
	}
	int now;//��¼��ǰ���ֵ����λ��
	int close=n-1;//��¼��ǰӦ�������λ��
	while(close!=0)
	{
		now=max(close);
		if(close==now)
		{
			close--;
		}
		else
		{
			if(now==0)
			{
				swap(close);
				close--;
			} 
			else
			{
				swap(now);
				swap(close);
				close--;
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
