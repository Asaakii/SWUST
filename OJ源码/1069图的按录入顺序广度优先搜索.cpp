#include <iostream>
#include <queue>

using namespace std;

int main()
{
	queue<int> s;
	int n;
	cin >> n;
	char str[100];
	char strr[100][2];
	cin >> str;
	for (int i=0;i<n;i++)
	{
		strr[i][0]=str[i];
		strr[i][1]='0';
	}
	int arr[100][100];
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
		{
			cin >> arr[i][j];
		}
	}
	char a;
	int b;
	cin >> a;
	for (int i=0;i<n;i++)
	{
		if (strr[i][0]==a)
		{
			b=i;
			break;
		}
	}
	strr[b][1]='1';
	s.push(b);
	cout << strr[b][0];
	while (s.size()>0)
	{
		int flag=0;
		int v=s.front();
		for (int i=0;i<n;i++)
		{
			if (arr[v][i]>0&&strr[i][1]=='0')
			{
				flag=1;
				strr[i][1]='1';
				cout << strr[i][0];
				s.push(i);
			}
		}
		s.pop();
	}
	return 0;
}
