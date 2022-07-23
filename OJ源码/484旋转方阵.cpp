#include<stdio.h>
#include<algorithm>
#include<iostream>
#include<iomanip>

using namespace std;

int main()
{
    int n;
    scanf("%d", &n);
    int a[25][25] = {0};
    int count = 1;
    int i = 0, j = 0, temp = 1;
    a[0][0] = 1;
    while (count < n*n)
    {
        while (i + 1 < n&& !a[i + 1][j])
        {
            count++;
            a[++i][j] = ++temp;
        }
        while (j + 1 < n && !a[i][j + 1])
        {
            count++;
            a[i][++j] = ++temp;
        }
        while (i - 1 >= 0 && !a[i - 1][j])
        {
            count++;
            a[--i][j] = ++temp;
        }
        while (j - 1 >= 0 && !a[i][j - 1])
        {
            count++;
            a[i][--j] = ++temp;
        }
    }
    for (i = 0;i < n;i++)
    {
        for (j = 0;j < n;j++)
            cout << setw(4) << setiosflags(ios::left) << a[i][j];
        printf("\n");
    }
    return 0;
}
