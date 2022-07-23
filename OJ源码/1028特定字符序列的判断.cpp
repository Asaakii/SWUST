#include <iostream>
#include <list>
#include <string>

using namespace std;

int main()
{
	string a;
	cin >> a;
	a.c_str();
	list<char> List1,List2;
	for (int i=0;a[i]!='#';i++)
	{
		if (a[i]!='@')
			List1.push_back(a[i]);
		else
		{
			for (int j=i+1;a[j]!='#';j++)
			{
				List2.push_front(a[j]);
			}
			break;
		}
	}
	int flag=1;
	list<char>::iterator p;
	list<char>::iterator q;
	for (p=List1.begin(),q=List2.begin();p!=List1.end()&&q!=List2.end();p++,q++)
	{
		if (*p!=*q)
		{
			flag=0;
			break;
		}
	}
	if (flag==0)
		cout << "no!";
	else
		cout << "yes!";
	return 0;
}
