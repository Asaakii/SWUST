#include<stdio.h>

int num[10002];

void Swap(int lv, int rv)
{
	int t = num[lv];
	num[lv] = num[rv];
	num[rv] = t;
}

int Partition(int left, int right)
{
	int i = left + 1;
	int j = right - 1;
	while (i <= j)
	{
		while (i <= j && num[j] >= num[left]) j--;
		while (i <= j && num[i] < num[left]) i++;
		if (i < j) Swap(i, j);
	}
	Swap(left, i - 1);
	return i - 1;
}

int sort(int left, int right)
{
	for (int i = left; i < right - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j < right; j++)
		{
			if (num[j] < num[min]) min = j;
		}
		Swap(min, i);
	}

	return (right + left) / 2;
}

int FindMid(int left, int right)
{

	if (left + 5 >= right)
	{
		return sort(left, right);
	}

	int time = (right - left) / 5;
	for (int i = 0; i < time; i++)
	{
		int tmp = sort(left + i * 5, left + i * 5 + 5);
		Swap(left + i, tmp);
	}
	return FindMid(left, left + time);
}

int Find(int left, int right, int k)
{
	int midNum = FindMid(left, right);
	Swap(left, midNum);

	int tk = Partition(left, right);
	if (tk + 1 == k) return num[tk];
	if (tk + 1 > k) return Find(left, tk, k);
	else return Find(tk + 1, right, k);
}

int main()
{
	int n, k;
	while (scanf("%d%d", &n, &k) != EOF)
	{

		for (int i = 0; i < n; i++)
		{
			scanf("%d", &num[i]);
		}

		int ans = Find(0, n, k);
		printf("%d\n", ans);
	}
	return 0;
}
