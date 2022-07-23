#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<string>
#include<vector>
#include<queue>
#define INF 0x3f3f3f3f
#define LL long long int

using namespace std;
 
struct node
{
	int count;
	int sumVa;
	vector<LL> army;
 
	//构造函数：初始化列表-->node():count(0),sumVa(0){};
	node()
	{
		count = 0;
		sumVa = 0;
		army.clear();
	}
};
 
int main()
{
	int n, Length;
	while (cin >> n >> Length)
	{
		int len[605];
		for (int i = 1; i <= n; i++)
			cin >> len[i];
 
		node dp[6005];			//必须写在main()
						//题目巨坑：输出最小字典序的程序
		for (int i = n; i >0; i--)	//只有也必须倒叙规划
		{
			int s = len[i];
			for (int j = Length; j >= 0; j--)
			{
				if (j >= s)
				{
					if (dp[j].count < dp[j - s].count + 1 || dp[j].count == dp[j - s].count + 1 && dp[j].sumVa <= dp[j - s].sumVa + s)
					{
						dp[j].count = dp[j - s].count + 1;
						dp[j].sumVa = dp[j - s].sumVa + s;
						dp[j].army  = dp[j - s].army;
						dp[j].army.push_back(s);
					}
				}
			}
		}
 
		cout << dp[Length].count << " " << dp[Length].sumVa << endl;
		for (int i = dp[Length].army.size() - 1; i >= 0; i--)
		{
			if (i != dp[Length].army.size() - 1)
				cout << " ";
			cout << dp[Length].army[i];
		}
		cout << endl;
	}
	return 0;
}

/*
9 50
2 3 13 8 80 20 21 22 23
*/

/*
5 49
2 3 13 8 23
*/