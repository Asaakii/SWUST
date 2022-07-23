#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int main()
{
	char s1[1000], s2[1000];
	int n, len1, len2;
	cin >> n;
	while (n--)
	{
		cin >> s1 >> s2;
		len1 = strlen(s1);
		len2 = strlen(s2);
		sort(s1, s1 + len1);
		sort(s2, s2 + len2);
		if (strcmp(s1, s2) == 0)
		{
			cout << "Yes" << endl;
		}
		else
		{
			cout << "No" << endl;
		}
	}
	return 0;
}
