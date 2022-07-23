#include <bits/stdc++.h>

using namespace std;

int main()
{
	int R[1000],n;
	cin >> n;
	for (int i=0;i<n;++i)
		cin >> R[i];
		
	if (R[1]<R[0])
		swap (R[0],R[1]);
		
	for (int i=0;i<n;++i)
		cout << R[i] << " ";
	return 0;
}
