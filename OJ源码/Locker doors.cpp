#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	int n(0),count(0);
	cin>>n;
	for (int i=1;pow(i,2)<=n;++i)
		count++;
	cout<<count<<endl;
	return 0;
}
