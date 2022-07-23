#include <iostream>

using namespace std;

int partition(int *p,int l,int r)
{
	int pivot=p[l];
	int s=l;
	for(int i=l+1;i<=r;i++)
	{
		if(p[i]<pivot)
		{
			s += 1;
			swap(p[s],p[i]);
		}
	}
	swap(p[l],p[s]);
	return s;
}

void quick_sort3(int arr[],int l,int r)
{
	int key=0;
	if(l<r)
	{
		key=partition(arr,l,r);
		quick_sort3(arr,l,key-1);
		quick_sort3(arr,key+1,r);
	}
}

int main()
{
	int arr[50001];
	int len;
	cin>>len;
	for(int j=0;j<len;j++)
		cin>>arr[j];
	quick_sort3(arr,0,len-1);
	for(int i=0;i<len;i++)
	{
		if(i!=len-1)
		cout<<arr[i] <<" ";
		else cout<<arr[i]<<" "<<endl;
	}
	return 0;
}
