#include <iostream>
#include <vector>
#include <list>

using namespace std;

int flag=0;
int Count=0;
class hashmap
{
public:
	hashmap(int size=1000)
	{
		arr.resize(size);
		sizement=size;
		currentsize=0;
	}
	int hash(int n)
	{
		int hashval=n%sizement;
		return hashval;
	}
	void put(int n)
	{
		int pos=hash(n);
		arr[pos].push_back(n);
		currentsize++;
	}
	int get(int n)
	{
		int x;
		int pos=hash(n);
		list<int>::iterator iter;
		for (iter=arr[pos].begin();iter!=arr[pos].end();iter++)
		{
			if (*iter==n)
			{
				x=*iter;
			}
			else
			{
				Count++;
			}
		}
		if (x==n)
		{
			flag=1;
			return pos;
		}
		else
		{
			return -1;
		}
	}
private:
	int currentsize;
	int sizement;
	vector<list<int> >arr;
};

int main()
{
	int m;
	cin >> m;
	int n;
	cin >> n;
	hashmap H(n);
	int x;
	for (int i=0;i<n;i++)
	{
		cin >> x;
		H.put(x);
	}
	int k;
	cin >> k;
	int pos=H.get(k);
	if (flag==1)
	{
		cout << pos << "," << Count;
	}
	else
	{
		cout << -1;
	}
	return 0;
}
