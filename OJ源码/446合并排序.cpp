#include <iostream>
 
using namespace std;

void merge(int a[],int left,int mid,int right,int temp[])
{
	int i = left;
	int j = mid + 1;
	int t = 0;
	while(i <= mid && j <= right)
	{
		if(a[i] <= a[j])
			temp[t++] = a[i++];
		else
			temp[t++] = a[j++];
	}
	while(i <= mid)         
		temp[t++] = a[i++];
	while(j <= right)
		temp[t++] = a[j++];
	for(i = 0; i < t; i++)
		a[left+i] = temp[i];
}

void sort(int temp[],int a[],int left,int right)
{
	if(left < right)
	{
		int mid = left + (right - left) / 2;
		sort(temp,a,left,mid);
		sort(temp,a,mid + 1,right);
		merge(a,left,mid,right,temp);
	}
}

int main()
{
	int num;
	cin >> num;
	int a[num] = {0};
	for(int i = 0; i < num; i++)
	{
		cin >> a[i];
	}
	int temp[num] = {0};
	sort(temp,a,0,num-1);
	int i;
	for(i = 0; i < num - 1; i++)
	{
		if((i + 1) % 10 == 0)
			cout << a[i] << endl;
		else 
			cout << a[i] <<"  ";
	}
	cout << a[i] << endl;
}
