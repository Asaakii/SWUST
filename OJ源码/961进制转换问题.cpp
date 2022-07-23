#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

int main()
{
	list<int> List;
	int m;
	cin >> m;
	while (m)
	{
		List.push_front(m%2);
		m=m/2;
	}
	list<int>::iterator iter;
	for (iter=List.begin();iter!=List.end();iter++)
	{
		cout << *iter;
	}
	return 0;
}
