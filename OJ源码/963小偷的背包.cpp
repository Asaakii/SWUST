#include <iostream>

using namespace std;

int test(int s,int n,int weight[1000])
{
	if (s!=0&&n<=0)
		return 0;
	if (s==0)
		return 1;
	if (test(s-weight[n-1],n-1,weight))
		return 1;
	test(s,n-1,weight);
}

int main()
{
	int s;
	int n;
	int weight[1000];
	cin >> s;
	cin >> n;
	for (int i=0;i<n;i++)
	{
		cin >> weight[i];
	}
	if (test(s,n,weight))
		cout << "yes!";
	else
		cout << "no!";
	return 0;
}
