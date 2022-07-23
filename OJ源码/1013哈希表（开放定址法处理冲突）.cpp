#include <iostream>
#include <vector>
#include <list>

using namespace std;

int flag=0;
int Count=1;
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
		if (arr[pos]==NULL)
		arr[pos]=n;
		else
		{
			while (arr[pos]!=NULL)
			{
				pos++;
				if (pos > sizement - 1)
					pos=0;
			}
			arr[pos]=n;
		}
		currentsize++;
	}
	int get(int n)
	{
		int x;
		int pos=hash(n);
		
		for (int i=pos; i<sizement;i++)
		{
			x=arr[i];
			if (x==n)
			{
				break;
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
	vector<int> arr;
};

int main()
{
	int m;
	cin >> m;
	int n;
	cin >> n;
	hashmap H(m);
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
