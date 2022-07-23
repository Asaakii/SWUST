#include <iostream>
#include <list> //使用顺序表 
#include <algorithm> //使用函数 

using namespace std;

int main()
{
	list<int> List;
	int n;
	cin >> n;
	int arr[1000];
	for (int i=0;i<n;i++)
	{
		cin >> arr[i];
		List.push_back(arr[i]); //将数组元素放入顺序表 
	}
	int m;
	cin >> m;
	int date;
	cin >> date;
	list<int>::iterator iter; //迭代器 
	iter = List.begin();
	for (int i=1;*iter!=m&&iter!=List.end();i++)
	{
		iter++;
	}
	List.insert(iter,date); //放入date在list后 
	iter = List.begin();
	for (int i=0;iter!=List.end();iter++)
	{
		cout << *iter << " ";
	}
	return 0;
}
