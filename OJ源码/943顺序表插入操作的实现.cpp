#include <iostream>
#include <list> //ʹ��˳��� 
#include <algorithm> //ʹ�ú��� 

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
		List.push_back(arr[i]); //������Ԫ�ط���˳��� 
	}
	int m;
	cin >> m;
	int date;
	cin >> date;
	list<int>::iterator iter; //������ 
	iter = List.begin();
	for (int i=1;*iter!=m&&iter!=List.end();i++)
	{
		iter++;
	}
	List.insert(iter,date); //����date��list�� 
	iter = List.begin();
	for (int i=0;iter!=List.end();iter++)
	{
		cout << *iter << " ";
	}
	return 0;
}
