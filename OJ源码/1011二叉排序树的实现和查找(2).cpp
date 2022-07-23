#include <bits/stdc++.h>

using namespace std;

int Search(int x,int l,int r,int a[],int times)//二分查找 
{
	int mid=l+r >> 1;
	if (x==a[mid])
		return times;//找到了，返回下标 
	if (l==r)
		return -1;//没找到，返回-1 
	return x<a[mid]?Search(x,l,mid,a,times+1):Search(x,mid+1,r,a,times+1);//比中间小在左边找，否则在右边找 
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
