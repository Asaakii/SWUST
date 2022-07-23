#include <bits/stdc++.h>

using namespace std;

void sift(int R[],int low,int high)
{
	int i=low,j=i<<1,tem=R[i];//i<<1==i*2,位运算快一点 
	while (j<=high)
	{
		if (j<high&&R[j]>R[j+1])
			++j;
		if (tem>R[j])
		{
			R[i]=R[j];
			i=j;
			j=i<<1;
		}
	}
	R[i]=tem;
}

int main()
{
	int R[1000],n;
	cin >> n;
	for (int i=1;i<=n;++i)
		cin >> R[i];
	for (int i=n/2;i>=1;--i)
		sift(R,i,n);//建堆 
	for (int i=1;i<=n;++i)
		cout << R[i] << " ";
	return 0;
}
