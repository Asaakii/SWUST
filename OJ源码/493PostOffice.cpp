#include <iostream>
#include <algorithm>

using namespace std;

bool cmp(int a, int b)
{
	return a < b;
}

int main()
{
	int ad[10005], ap[10005];
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> ad[i] >> ap[i];
	}
	sort(ad, ad + n, cmp);
	sort(ap, ap + n, cmp);

	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += abs(ad[n / 2] - ad[i]);
		sum += abs(ap[n / 2] - ap[i]);
	}
	cout << sum << endl;
	return 0;
}
