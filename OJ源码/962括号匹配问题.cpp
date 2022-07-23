#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

int main()
{
	char arr[1000];
	cin >> arr;
	stack<char> st;
	for (int i=0;arr[i]!='\0';i++)
	{
		if (st.empty())
			st.push(arr[i]);
		else if ((st.top()=='['&&arr[i]==']')||(st.top()=='('&&arr[i]==')'))
		{
			st.pop();
		}
		else
		{
			st.push(arr[i]);
		}
	}
	if (st.empty())
		cout << "YES";
	else
		cout << "NO";
	return 0;
}
