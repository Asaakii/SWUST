#include <bits/stdc++.h>

using namespace std;

int Search(int x,int l,int r,int a[],int times)//���ֲ��� 
{
	int mid=l+r >> 1;
	if (x==a[mid])
		return times;//�ҵ��ˣ������±� 
	if (l==r)
		return -1;//û�ҵ�������-1 
	return x<a[mid]?Search(x,l,mid,a,times+1):Search(x,mid+1,r,a,times+1);//���м�С������ң��������ұ��� 
}

int main()
{
	int a[1000],x,n;
	cin >> n;
	for (int i=0;i<n;i++)
		cin >> a[i];
	cin >> x;
	sort(a,a+n);
	
	cout << Search(x,0,n-1,a,1);
	return 0;
}
