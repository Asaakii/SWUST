#include<iostream>
#include<map>
#include<set>

using namespace std;
 
//合并果子  
int main()
{
	int n;
	cin >> n;
	multiset<int> data;
	multiset<int>::iterator is;
	int sum = 0;
	int i, tmp;
	for (i = 0; i < n; i++)
	{
		cin >> tmp;
		data.insert(tmp);
	}
	while (data.size()>1)
	{
		tmp = 0;
		is = data.begin();
		tmp += *is;
		data.erase(is);
 
		is = data.begin();
		tmp += *is;
		data.erase(is);
 
		data.insert(tmp);
		sum += tmp;
	}
	cout << sum;
	system("pause");
	return 0;
}
