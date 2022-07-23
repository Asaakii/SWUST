#include<bits/stdc++.h>
#define int long long
#define lowbit(x) (x &(-x))

using namespace std;

const int INF=0x3f3f3f3f;
const double PI=acos(-1.0);
const double eps=1e-10;
const int M=1e9+7;
const int N=1e5+5;
typedef long long ll;
typedef pair<int,int> PII;
int getPriority(char c)
{
//判断运算符优先级
    int level=0;
	switch(c)
	{       
		case '(':level=1;break;        
		case '+':case '-':level=2;break;
		case '*':case '/':level=3;break;        
		default:break;    
	}
	return level;
}
string s,str;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	
	cin>>s;
	stack<char> st;
	for(int i=0;i<s.length();i++)
	{
		if(isalpha(s[i]))//如果是字母
			str+=s[i];
		else if(s[i]=='(')
			st.push(s[i]);
		else if(s[i]==')'){
			while(st.top()!='(')
			{
				str+=st.top();
				st.pop();
			}
			st.pop(); 
		}
		else
		{
			while(!st.empty()&&getPriority(s[i])<=getPriority(st.top()))
			{
				str+=st.top();
				st.pop();
			}
			st.push(s[i]);
		}
	}
	while(!st.empty())
	{
		str+=st.top();
		st.pop();
	}
	cout<<str;
	return 0;
}
