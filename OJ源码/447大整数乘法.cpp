#include<iostream>
#include<algorithm>
#include<string.h>
#include<stdio.h>

using namespace std;
 
void Compute(char *a, char *b, char *c)
{
	int n, m;
	m = strlen(a) - 1;
	n = strlen(b) - 1;
	for (int i = m; i >= 0; i--)
	{
		a[i] -= '0';
	}
	for (int i = n; i >= 0; i--)
	{
		b[i] -= '0';
	}
	c[m + n + 2] = '\0';
	long carry = 0;
	long sum;
	int j;
	for (int i = m + n; i >= 0; i--)
	{
		sum = carry;
		if ((j = (i - m)) < 0)
		{
			j = 0;
		}
		for (; j <= i&&j <= n; j++)
		{
			sum += a[i - j] * b[j];
		}
		c[i + 1] = sum % 10 + '0';
		carry = sum / 10;
	}
	c[0] = carry + '0';
}
 
int main()
{
	int k;
	char str1[105];
	char str2[105];
	char ans[10000];
	while(cin >> k)
	{
		scanf("%s%s", str1, str2);
		Compute(str1, str2, ans);
		if(ans[0]!='0')
		printf("%s", ans);
		else
		{
			for (int i = 1; i < strlen(ans); i++)
			{
				cout << ans[i];
			}
		}
		cout << endl;
	}
	return 0;
}
